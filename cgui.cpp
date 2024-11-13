#include "cgui.h"
#include "ui_cgui.h"

CGui::CGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CGui)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sig_erreur(QString)), this, SLOT(on_erreur(QString)));
    setIhm(true); // autorise paramétrage
    ui->laNoir->setPixmap(QPixmap("./noir.gif"));
    ui->laNoir->setVisible(true);
    ui->laRouge->setPixmap(QPixmap("./rouge.png"));
    ui->laRouge->setVisible(false);
    ui->cbPorts->addItems(CPeriphRs232::portsDisponibles());  // affichage des ports disponibles

    // états
    _affLibre=true;
    _etatServeur=false;
    _seuil=false;   // dépassement seuil mesure

    // initialisation de la mémoire partagée
    _shm = new CSharedMemory(this, sizeof(T_SHM_DATA));
    _shm->attacherOuCreer();
    // intanciation de l'objet LED
    _led = new CLed(this, GPIO_LED);

    // lance thread CBoutonPoussoir
    _thBp = new QThread();
    _bp = new CBoutonPoussoir(nullptr, GPIO_BOUTONPOUSSOIR);
    _bp->moveToThread(_thBp);
    connect(_bp, &CBoutonPoussoir::sig_erreur, this, &CGui::on_erreur);
    connect(_thBp, &QThread::finished, _bp, &CBoutonPoussoir::deleteLater);
    connect(_bp, &CBoutonPoussoir::sig_etatBouton, this, &CGui::on_etatBouton);
    connect(this, &CGui::sig_goBp, _bp, &CBoutonPoussoir::on_go);
    _thBp->start();
    emit sig_goBp();


    // instanciation de l'afficheur LCD
    _aff = new CAff_i2c_GroveLcdRgb();
    connect(_aff, &CAff_i2c_GroveLcdRgb::sig_erreur, this, &CGui::on_erreur);

    // init des pointeurs vers capteurs
    _thBp = nullptr;
    _thSht20 = nullptr;
    _thTc72 = nullptr;
    _periph = NULL;
    _clientTcp = NULL;
    _serveurTcp = NULL;
    _bdd = NULL;

    // init timer envoi mesures vers serveur TCP
    _interServeur = new QTimer(this);
    connect(_interServeur, SIGNAL(timeout()), this, SLOT(on_timerServeur()));
    // init du timer de récupération des mesures
    _interMes = new QTimer(this);
    connect(_interMes, &QTimer::timeout, this, &CGui::on_timerMes);
    // init timer affichage LCD
    _interLcd = new QTimer(this);
    connect(_interLcd, &QTimer::timeout, this, &CGui::on_timerLcd);
    // init timer maj de la bdd
    _interSgbd = new QTimer(this);
    connect(_interSgbd, &QTimer::timeout, this, &CGui::on_timerSgbd);
}

CGui::~CGui()
{
    stopAll(); // stop timers et détruit mesures
    // détruit les timers
    _interServeur->stop();
    delete _interServeur;
    _interMes->stop();
    delete _interMes;
    _interLcd->stop();
    delete _interLcd;
    _interSgbd->stop();
    delete _interSgbd;
    // détruit les objets
    delete _led;
    delete _aff;
    if (_thBp->isRunning()) {
        _bp->_fin=true;
        _thBp->wait(TEMPS);
        delete _thBp;
    } // if bt
    // détruit les threads
    _shm->detach();
    delete _shm;
    delete ui;  // toujours en dernier
}

void CGui::on_pbStartStop_clicked()
{
//   bool ok;
   int etat;
   if (ui->pbStartStop->text() == "Start acquisitions") etat = 1; else etat = 2;

   switch(etat) {
   case 1: // start acquisition
       // réglages IHM de départ
       setIhm(false);
       ui->pbStartStop->setText("Stop acquisitions");

       // instanciation de la BDD
       _bdd = new CBdd(this);
       connect(_bdd, &CBdd::sig_erreur, this, &CGui::on_erreur);
       _etatBdd = _bdd->connecter(ui->leAdrSgbd->text(), ui->leNomBdd->text(), ui->leNomBdd->text(), ui->lePassSgbd->text());

       // instanciation du periphRS232C
       _periph = new CPeriphRs232(this, "/dev/"+ui->cbPorts->currentText());
       connect(_periph, &CPeriphRs232::sig_erreur, this, &CGui::on_erreur);
       connect(_periph, &CPeriphRs232::sig_data, this, &CGui::on_recevoirDataDuPeriph);
       _periph->initialiser(ui->cbVitesse->currentText(),
                             ui->cbBits->currentText(),
                             ui->cbParite->currentText(),
                             ui->cbStop->currentText(),
                             QString::number(QSerialPort::NoFlowControl));

       // instanciation du serveur TCP
       _serveurTcp = new CServeurTcp(this);
       connect(_serveurTcp, &CServeurTcp::sig_evenement, this, &CGui::on_erreur);
       connect(_serveurTcp, &CServeurTcp::sig_erreur, this, &CGui::on_erreur);

       // connexion au serveur réseau
       _clientTcp = new CClientTcp(this);
       connect(_clientTcp, &CClientTcp::sig_evenement, this, &CGui::on_erreur);
       connect(_clientTcp, &CClientTcp::sig_erreur, this, &CGui::on_erreur);
       connect(_clientTcp, &CClientTcp::sig_data, this, &CGui::on_erreur);
       _etatServeur = _clientTcp->connecter(ui->leAdrServ->text(), ui->lePortServ->text());

       // lance les thread capteurs
       _thSht20 = new QThread();
       _sht20 = new CCapteur_I2c_SHT20(this,1);
       _sht20->moveToThread(_thSht20);
       connect(_sht20, &CCapteur_I2c_SHT20::sig_erreur, this, &CGui::on_erreur);
       connect(this, &CGui::sig_goCapt, _sht20, &CCapteur_I2c_SHT20::on_go);
       connect(_thSht20, &QThread::finished, _sht20, &CCapteur_I2c_SHT20::deleteLater);
       _thSht20->start();

       _thTc72 = new QThread();
       _tc72 = new CCapteur_Spi_TC72(this, '0', 0);
       _tc72->moveToThread(_thTc72);
       connect(_tc72, &CCapteur_Spi_TC72::sig_erreur, this, &CGui::on_erreur);
       connect(this, &CGui::sig_goCapt, _tc72, &CCapteur_Spi_TC72::on_go);
       connect(_thTc72, &QThread::finished, _tc72, &CCapteur_Spi_TC72::deleteLater);
       _thTc72->start();

       emit sig_goCapt();

       // lance les timers
       _interSgbd->start(ui->leInterBdd->text().toInt()*1000);
       _interServeur->start(ui->leInterServ->text().toInt()*1000);
       _interMes->start(ui->leInterCapt->text().toInt()*1000);
       _interLcd->start(ui->leInterCapt->text().toInt()*1000);
       break;

   default: // stop acquisitions
       stopAll();
       ui->pbStartStop->setText("Start acquisitions");
       setIhm(true);
       break;
   } // sw
}

void CGui::on_erreur(QString mess)
{
    //QMessageBox::warning(this, "Erreur !", mess);
    ui->teTexte->append(mess);
}

void CGui::on_etatBouton(bool etat)
{
    ui->lEtatBouton->setText((etat?"Bouton relâché !":"Bouton appuyé !"));
}

void CGui::on_pbOnOffLed_clicked()
{
    int etat;
    if (ui->pbOnOffLed->text() == "Allumer") etat = 1; else etat = 2;

    switch(etat) {
    case 1: // allumer
        ui->laRouge->setVisible(true);
        ui->laNoir->setVisible(false);
        ui->pbOnOffLed->setText("Eteindre");
        _led->switchOn();
        break;
    default:  // éteindre
        ui->laRouge->setVisible(false);
        ui->laNoir->setVisible(true);
        ui->pbOnOffLed->setText("Allumer");
        _led->switchOff();
        break;
    } // sw
}

void CGui::on_timerMes()
{
    int noMes=0;
    // vérification des seuils
    _seuil = false;
    if (_shm->lire(0) > ui->leSeuilTempSpi->text().toFloat()) {_seuil=true;noMes+=1;}
    if (_shm->lire(1) > ui->leSeuilTempI2c->text().toFloat()) {_seuil=true;noMes+=2;}
    if (_shm->lire(2) > ui->leSeuilHumI2c->text().toFloat()) {_seuil=true;noMes+=4;}
    ui->leTempSpi->setText(QString::number(_shm->lire(0),'f',1));  // temp spi
    ui->leTempI2c->setText(QString::number(_shm->lire(1),'f',1));  // temp i2c
    ui->leHumI2c->setText(QString::number(_shm->lire(2),'f',1));  // hum i2c
    if (_seuil) {
        _led->switchOn();
        ui->laNoir->setVisible(false);
        ui->laRouge->setVisible(true);
        ui->pbOnOffLed->setEnabled(false);
        if ((noMes&0x01)==1) ui->leTempSpi->setStyleSheet("background: red");
        else ui->leTempSpi->setStyleSheet("background: white");
        if ((noMes&0x02)==2) ui->leTempI2c->setStyleSheet("background: red");
        else ui->leTempI2c->setStyleSheet("background: white");
        if ((noMes&0x04)==4) ui->leHumI2c->setStyleSheet("background: red");
        else ui->leHumI2c->setStyleSheet("background: white");
    } else {
        if (!ui->pbOnOffLed->isEnabled()) {
            _led->switchOff();
            ui->laNoir->setVisible(true);
            ui->laRouge->setVisible(false);
            ui->pbOnOffLed->setEnabled(true);
            ui->leTempSpi->setStyleSheet("background: white");
            ui->leTempI2c->setStyleSheet("background: white");
            ui->leHumI2c->setStyleSheet("background: white");
        } // if enabled
    } // else
}

void CGui::on_timerSgbd()
{
    if (_etatBdd) {
        for(int i=0 ; i<NBMESURES ; i++)
            _bdd->sauverMesure(i, _shm->lire(i));
    } // if
}

void CGui::on_timerServeur()
{
    if (_etatServeur) {
        QString mesI2c = "SHC20 Temp:"+QString::number(_shm->lire(1),'f',1)+"°C"+
                " Hum:"+QString::number(_shm->lire(2),'f',1);
        _clientTcp->emettre(mesI2c);
        QString mesSpi = "TC72 Temp:"+QString::number(_shm->lire(0),'f',1)+"°C";
        _clientTcp->emettre(mesSpi);
    } // if
}

void CGui::on_timerLcd()
{
    if(_affLibre)
        _aff->afficherMesures(_shm->lire(0),_shm->lire(1), _shm->lire(2), _seuil);
}

void CGui::setIhm(bool t)
{
    ui->gbIntervalle->setEnabled(t);
    ui->gbSgbd->setEnabled(t);
    ui->gbVS->setEnabled(t);
    ui->gbServeur->setEnabled(t);
    ui->gbEcranRs->setEnabled(!t);
}

void CGui::stopAll()
{
    _interMes->stop();
    _interServeur->stop();
    _interSgbd->stop();
    _interLcd->stop();
    _aff->clear();
    _aff->setColorOff();
    if (_periph != NULL) {
        delete _periph;
        _periph=NULL;
    } // if serv
    if (_serveurTcp != NULL) {
        delete _serveurTcp;
        _serveurTcp=NULL;
    } // if serv
    if (_clientTcp != NULL) {
        delete _clientTcp;
        _clientTcp=NULL;
    } // if client
    if (_thSht20 != NULL) {
        _sht20->_fin=true;
        _thSht20->wait(TEMPS); // max 3s
        delete _thSht20;
        _thSht20=NULL;
    } // if i2c
    if (_thTc72 != NULL) {
        _tc72->_fin=true;
        _thTc72->wait(TEMPS);
        delete _thTc72;
        _thTc72=NULL;
    } // if spi
    if (_bdd != NULL) {
        delete _bdd;
        _bdd = NULL;
    } // if bdd
}

void CGui::on_pbLcd_clicked()
{
    if (_affLibre) {
        _affLibre = false;
        _thAff = new QThread();
        _aff->moveToThread(_thAff);
        connect(_thAff, &QThread::started, _aff, &CAff_i2c_GroveLcdRgb::on_sequenceBienvenue);
        connect(_aff, &CAff_i2c_GroveLcdRgb::sig_workFinished, _thAff, &QThread::quit);
        //connect(_thAff, &QThread::finished, _aff, &CAff_i2c_GroveLcdRgb::deleteLater);
        connect(_thAff, &QThread::finished, this, &CGui::on_finished);
        if (_interLcd->isActive()) {
            _interLcd->stop();
            // 2024 connect(_thAff, &QThread::finished, _interLcd, &QTimer::start);
        } // if isactive
        _thAff->start();
    } // if libre
}

void CGui::on_finished()
{
    _affLibre = true;
    delete _thAff;
    _interLcd->start();
}

void CGui::on_recevoirDataDuPeriph(QString data)
{
    ui->teRecevoir->append(data);
}

void CGui::on_pbEnvoyer_clicked()
{
    _periph->emettre(ui->leEnvoyer->text());
}
