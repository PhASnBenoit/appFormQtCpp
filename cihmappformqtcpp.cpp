#include "cihmappformqtcpp.h"
#include "ui_cihmappformqtcpp.h"

CIhmAppFormQtCpp::CIhmAppFormQtCpp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CIhmAppFormQtCpp)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
    setIhm(true); // autorise paramétrage
    ui->laNoir->setPixmap(QPixmap("./noir.gif"));
    ui->laNoir->setVisible(true);
    ui->laRouge->setPixmap(QPixmap("./rouge.png"));
    ui->laRouge->setVisible(false);
    ui->cbPorts->addItems(CPeriphRs232::portsDisponibles());  // affichage des ports disponibles

    // états
    m_affLibre=true;
    m_etatServeur=false;
    m_seuil=false;   // dépassement seuil mesure

    // initialisation de la mémoire partagée
    m_shm = new CSharedMemory(this, NBMESURES*sizeof(float));
    m_shm->attacherOuCreer();
    // intanciation de l'objet LED
    m_led = new CLed(this, GPIO_LED);

    // lance thread CBoutonPoussoir
    m_thBt = new CBoutonPoussoir(this, GPIO_BOUTONPOUSSOIR);
    connect(m_thBt, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
    connect(m_thBt, SIGNAL(sigEtatBouton(bool)), this, SLOT(on_etatBouton(bool)));
    m_thBt->start();

    // instanciation de l'afficheur LCD
    m_aff = new CAff_i2c_GroveLcdRgb();
    connect(m_aff, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));

    // init des pointeurs vers capteurs
    m_thI2c = NULL;
    m_thSpi = NULL;
    m_periph = NULL;
    m_clientTcp = NULL;
    m_serveurTcp = NULL;
    m_bdd = NULL;

    // init timer envoi mesures vers serveur TCP
    m_interServeur = new QTimer(this);
    connect(m_interServeur, SIGNAL(timeout()), this, SLOT(on_timerServeur()));
    // init du timer de récupération des mesures
    m_interMes = new QTimer(this);
    connect(m_interMes, SIGNAL(timeout()), this, SLOT(on_timerMes()));
    // init timer affichage LCD
    m_interLcd = new QTimer(this);
    connect(m_interLcd, SIGNAL(timeout()), this, SLOT(on_timerLcd()));
    // init timer maj de la bdd
    m_interSgbd = new QTimer(this);
    connect(m_interSgbd, SIGNAL(timeout()), this, SLOT(on_timerSgbd()));
}

CIhmAppFormQtCpp::~CIhmAppFormQtCpp()
{
    stopAll(); // stop timers et détruit mesures
    // détruit les timers
    m_interServeur->stop();
    delete m_interServeur;
    m_interMes->stop();
    delete m_interMes;
    m_interLcd->stop();
    delete m_interLcd;
    m_interSgbd->stop();
    delete m_interSgbd;
    // détruit les objets
    delete m_led;
    delete m_aff;
    if (m_thBt->isRunning()) {
        m_thBt->m_fin=true;
        m_thBt->wait(TEMPS);
        delete m_thBt;
    } // if bt
    // détruit les threads
    m_shm->detach();
    delete m_shm;
    delete ui;  // toujours en dernier
}

void CIhmAppFormQtCpp::on_pbStartStop_clicked()
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
       m_bdd = new CBdd(this);
       connect(m_bdd, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       m_etatBdd = m_bdd->connecter(ui->leAdrSgbd->text(), ui->leNomBdd->text(), ui->leNomBdd->text(), ui->lePassSgbd->text());

       // instanciation du periphRS232C
       m_periph = new CPeriphRs232(this, "/dev/"+ui->cbPorts->currentText());
       connect(m_periph, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       connect(m_periph, SIGNAL(sigData(QString)), this, SLOT(on_recevoirDataDuPeriph(QString)));
       m_periph->initialiser(ui->cbVitesse->currentText(),
                             ui->cbBits->currentText(),
                             ui->cbParite->currentText(),
                             ui->cbStop->currentText(),
                             QString::number(QSerialPort::NoFlowControl));

       // instanciation du serveur TCP
       m_serveurTcp = new CServeurTcp(this);
       connect(m_serveurTcp, SIGNAL(sigEvenement(QString)), this, SLOT(on_Erreur(QString)));
       connect(m_serveurTcp, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));

       // connexion au serveur réseau
       m_clientTcp = new CClientTcp(this);
       connect(m_clientTcp, SIGNAL(sigEvenement(QString)), this, SLOT(on_Erreur(QString)));
       connect(m_clientTcp, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       connect(m_clientTcp, SIGNAL(sigData(QString)), this, SLOT(on_Erreur(QString)));
       m_etatServeur = m_clientTcp->connecter(ui->leAdrServ->text(), ui->lePortServ->text());

       // lance les thread capteurs
       m_thI2c = new CCapteur_I2c_SHT20(this,1);
       connect(m_thI2c, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       connect(m_thI2c, SIGNAL(finished()), m_thI2c, SLOT(deleteLater()));
       connect(m_thI2c, SIGNAL(destroyed(QObject*)), m_thI2c, SLOT(deleteLater()));
       m_thI2c->start();

       m_thSpi = new CCapteur_Spi_TC72(this, '0', 0);
       connect(m_thSpi, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       connect(m_thSpi, SIGNAL(finished()), m_thI2c, SLOT(deleteLater()));
       connect(m_thSpi, SIGNAL(destroyed(QObject*)), m_thI2c, SLOT(deleteLater()));
       m_thSpi->start();

       // lance les timers
       m_interSgbd->start(ui->leInterBdd->text().toInt()*1000);
       m_interServeur->start(ui->leInterServ->text().toInt()*1000);
       m_interMes->start(ui->leInterCapt->text().toInt()*1000);
       m_interLcd->start(ui->leInterCapt->text().toInt()*1000);
       break;

   default: // stop acquisitions
       stopAll();
       ui->pbStartStop->setText("Start acquisitions");
       setIhm(true);
       break;
   } // sw
}

void CIhmAppFormQtCpp::on_Erreur(QString mess)
{
    //QMessageBox::warning(this, "Erreur !", mess);
    ui->teTexte->append(mess);
}

void CIhmAppFormQtCpp::on_etatBouton(bool etat)
{
    ui->lEtatBouton->setText((etat?"Bouton relâché !":"Bouton appuyé !"));
}

void CIhmAppFormQtCpp::on_pbOnOffLed_clicked()
{
    int etat;
    if (ui->pbOnOffLed->text() == "Allumer") etat = 1; else etat = 2;

    switch(etat) {
    case 1: // allumer
        ui->laRouge->setVisible(true);
        ui->laNoir->setVisible(false);
        ui->pbOnOffLed->setText("Eteindre");
        m_led->switchOn();
        break;
    default:  // éteindre
        ui->laRouge->setVisible(false);
        ui->laNoir->setVisible(true);
        ui->pbOnOffLed->setText("Allumer");
        m_led->switchOff();
        break;
    } // sw
}

void CIhmAppFormQtCpp::on_timerMes()
{
    int noMes=0;
    // vérification des seuils
    m_seuil = false;
    if (m_shm->lire(0) > ui->leSeuilTempSpi->text().toFloat()) {m_seuil=true;noMes+=1;}
    if (m_shm->lire(1) > ui->leSeuilTempI2c->text().toFloat()) {m_seuil=true;noMes+=2;}
    if (m_shm->lire(2) > ui->leSeuilHumI2c->text().toFloat()) {m_seuil=true;noMes+=4;}
    ui->leTempSpi->setText(QString::number(m_shm->lire(0),'f',1));  // temp spi
    ui->leTempI2c->setText(QString::number(m_shm->lire(1),'f',1));  // temp i2c
    ui->leHumI2c->setText(QString::number(m_shm->lire(2),'f',1));  // hum i2c
    if (m_seuil) {
        m_led->switchOn();
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
            m_led->switchOff();
            ui->laNoir->setVisible(true);
            ui->laRouge->setVisible(false);
            ui->pbOnOffLed->setEnabled(true);
            ui->leTempSpi->setStyleSheet("background: white");
            ui->leTempI2c->setStyleSheet("background: white");
            ui->leHumI2c->setStyleSheet("background: white");
        } // if enabled
    } // else
}

void CIhmAppFormQtCpp::on_timerSgbd()
{
    if (m_etatBdd) {
        for(int i=0 ; i<NBMESURES ; i++)
            m_bdd->sauverMesure(i, m_shm->lire(i));
    } // if
}

void CIhmAppFormQtCpp::on_timerServeur()
{
    if (m_etatServeur) {
        QString mesI2c = "SHC20 Temp:"+QString::number(m_shm->lire(1),'f',1)+"°C"+
                " Hum:"+QString::number(m_shm->lire(2),'f',1);
        m_clientTcp->emettre(mesI2c);
        QString mesSpi = "TC72 Temp:"+QString::number(m_shm->lire(0),'f',1)+"°C";
        m_clientTcp->emettre(mesSpi);
    } // if
}

void CIhmAppFormQtCpp::on_timerLcd()
{
    if(m_affLibre)
        m_aff->afficherMesures(m_shm->lire(0),m_shm->lire(1), m_shm->lire(2), m_seuil);
}

void CIhmAppFormQtCpp::setIhm(bool t)
{
    ui->gbIntervalle->setEnabled(t);
    ui->gbSgbd->setEnabled(t);
    ui->gbVS->setEnabled(t);
    ui->gbServeur->setEnabled(t);
    ui->gbEcranRs->setEnabled(!t);
}

void CIhmAppFormQtCpp::stopAll()
{
    m_interMes->stop();
    m_interServeur->stop();
    m_interSgbd->stop();
    m_interLcd->stop();
    m_aff->clear();
    m_aff->setColorOff();
    if (m_periph != NULL) {
        delete m_periph;
        m_periph=NULL;
    } // if serv
    if (m_serveurTcp != NULL) {
        delete m_serveurTcp;
        m_serveurTcp=NULL;
    } // if serv
    if (m_clientTcp != NULL) {
        delete m_clientTcp;
        m_clientTcp=NULL;
    } // if client
    if (m_thI2c != NULL) {
        m_thI2c->m_fin=true;
        m_thI2c->wait(TEMPS); // max 3s
        delete m_thI2c;
        m_thI2c=NULL;
    } // if i2c
    if (m_thSpi != NULL) {
        m_thSpi->m_fin=true;
        m_thSpi->wait(TEMPS);
        delete m_thSpi;
        m_thSpi=NULL;
    } // if spi
    if (m_bdd != NULL) {
        delete m_bdd;
        m_bdd = NULL;
    } // if bdd
}

void CIhmAppFormQtCpp::on_pbLcd_clicked()
{
    if (m_affLibre) {
        m_affLibre = false;
        m_thAff = new QThread();
        m_aff->moveToThread(m_thAff);
        connect(m_thAff, SIGNAL(started()), m_aff, SLOT(sequenceBienvenue()));
        connect(m_aff, SIGNAL(sigWorkFinished()), m_thAff, SLOT(quit()));
        connect(m_thAff, SIGNAL(finished()), m_thAff, SLOT(deleteLater()));
        connect(m_thAff, SIGNAL(finished()), this, SLOT(onFinished()));
        if (m_interLcd->isActive()) {
            m_interLcd->stop();
            connect(m_thAff, SIGNAL(finished()), m_interLcd, SLOT(start()));
        } // if isactive
        m_thAff->start();
    } // if libre
}

void CIhmAppFormQtCpp::onFinished()
{
    m_affLibre = true;
    delete m_thAff;
}

void CIhmAppFormQtCpp::on_recevoirDataDuPeriph(QString data)
{
    ui->teRecevoir->append(data);
}

void CIhmAppFormQtCpp::on_pbEnvoyer_clicked()
{
    m_periph->emettre(ui->leEnvoyer->text());
}
