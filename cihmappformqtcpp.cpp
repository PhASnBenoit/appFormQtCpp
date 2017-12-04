#include "cihmappformqtcpp.h"
#include "ui_cihmappformqtcpp.h"

CIhmAppFormQtCpp::CIhmAppFormQtCpp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CIhmAppFormQtCpp)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
    setIhm(true);

    // états
    m_affLibre=true;

    // BDD
    m_bdd = QSqlDatabase::addDatabase("QMYSQL");
    if (!m_bdd.isValid()) {
        emit sigErreur("CIhmAppFormQtCpp::CIhmAppFormQtCpp Driver BDD non reconnu !");
    } // if bdd

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

    // init des pointeurs vers capteurs
    m_thI2c = NULL;
    m_thSpi = NULL;

    m_interServeur = new QTimer(this);
    connect(m_interServeur, SIGNAL(timeout()), this, SLOT(on_timerServeur()));
/*
    m_interPeriph = new QTimer(this);
    connect(m_interPeriph, SIGNAL(timeout()), this, SLOT(on_timerPeriph()));
    m_interSgbd = new QTimer(this);
    connect(m_interSgbd, SIGNAL(timeout()), this, SLOT(on_timerSgbd()));
*/
    // init du timer de récupération des mesures
    m_interMes = new QTimer(this);
    connect(m_interMes, SIGNAL(timeout()), this, SLOT(on_timerMes()));
    // init timer affichage LCD
    m_interLcd = new QTimer(this);
    connect(m_interLcd, SIGNAL(timeout()), this, SLOT(on_timerLcd()));
}

CIhmAppFormQtCpp::~CIhmAppFormQtCpp()
{
/*    delete m_interServeur;
    delete m_interSgbd;
    delete m_interPeriph;
*/
    m_interMes->stop();
    delete m_interMes;
    delete m_led;
    delete m_aff;
    delete m_clientTcp;
    if (m_thBt->isRunning()) {
        m_thBt->m_fin=true;
        m_thBt->wait(3000);
        delete m_thBt;
    } // if bt
    if (m_thI2c->isRunning()) {
        m_thI2c->m_fin=true;
        m_thI2c->wait(3000); // max 3s
        delete m_thI2c;
    } // if i2c
    if (m_thSpi->isRunning()) {
        m_thSpi->m_fin=true;
        m_thSpi->wait(3000);
        delete m_thSpi;
    } // if spi
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
/*
       // ouverture de la base de données
       m_bdd.setHostName(ui->leAdrSgbd->text());
       m_bdd.setDatabaseName(ui->leNomBdd->text());
       m_bdd.setUserName(ui->leUserSgbd->text());
       m_bdd.setPassword(ui->lePassSgbd->text());
       ok = m_bdd.open();
       if (!ok) {
           emit sigErreur("CIhmAppFormQtCpp::on_pbStartStop_clicked Ouverture de la BDD impossible !");
           return;
       } // if ok
*/
       // connexion au serveur réseau
       m_clientTcp = new CClientTcp(this);
       connect(m_clientTcp, SIGNAL(sigEvenement(QString)), this, SLOT(on_Erreur(QString)));
       connect(m_clientTcp, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       m_clientTcp->connecter(ui->leAdrServ->text(), ui->lePortServ->text());

       // lance les thread capteurs
       m_thI2c = new CCapteur_I2c_SHT20(this);
       connect(m_thI2c, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       connect(m_thI2c, SIGNAL(finished()), m_thI2c, SLOT(deleteLater()));
       connect(m_thI2c, SIGNAL(destroyed(QObject*)), m_thI2c, SLOT(deleteLater()));
       m_thI2c->start();

//       m_tc72 = new CSpiIoctl();
       m_thSpi = new CCapteur_Spi_TC72(this, 0, 0);
       connect(m_thSpi, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       connect(m_thSpi, SIGNAL(finished()), m_thI2c, SLOT(deleteLater()));
       connect(m_thSpi, SIGNAL(destroyed(QObject*)), m_thI2c, SLOT(deleteLater()));
       m_thSpi->start();
/*
       // ouvrir le port série avec le terminal
       m_thPeriph = new CPeriphRs232(this, "/dev/"+ui->cbPorts->currentText(), ui->leInterPeriph->text().toInt()*1000);
       connect(m_thPeriph, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       m_thPeriph->start();
*/
       // lance les timers
       //       m_interSgbd->start(ui->leInterBdd->text().toInt()*1000);
       //       m_interPeriph->start(ui->leInterPeriph->text().toInt()*1000);
       m_interServeur->start(ui->leInterServ->text().toInt()*1000);
       m_interMes->start(ui->leInterCapt->text().toInt()*1000);
       m_interLcd->start(ui->leInterCapt->text().toInt()*1000);
       break;

   default: // stop acquisitions
       m_interServeur->stop();
       delete m_interServeur;
       delete m_interLcd;
//       m_interSgbd->stop();
//       delete m_interSgbd;
//       delete m_thPeriph;
       delete m_clientTcp;
       if (m_thI2c->isRunning()) {
           m_thI2c->m_fin=true;
           m_thI2c->wait(3000); // max 3s
           delete m_thI2c;
       } // if i2c
       if (m_thSpi->isRunning()) {
           m_thSpi->m_fin=true;
           m_thSpi->wait(3000);
           delete m_thSpi;
       } // if spi
//       delete m_tc72;
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
    ui->leTempSpi->setText(QString::number(m_shm->lire(0),'f',1));  // temp spi
    ui->leTempI2c->setText(QString::number(m_shm->lire(1),'f',1));  // temp i2c
    ui->leHumI2c->setText(QString::number(m_shm->lire(2),'f',1));  // hum i2c
}

void CIhmAppFormQtCpp::on_timerSgbd()
{

}

void CIhmAppFormQtCpp::on_timerServeur()
{
    QString mesI2c = "SHC20 Temp:"+QString::number(m_shm->lire(1),'f',1)+"°C"+
            " Hum:"+QString::number(m_shm->lire(2),'f',1);
    m_clientTcp->emettre(mesI2c);
    QString mesSpi = "TC72 Temp:"+QString::number(m_shm->lire(0),'f',1)+"%RH";
    m_clientTcp->emettre(mesSpi);
}

void CIhmAppFormQtCpp::on_timerPeriph()
{
    
}

void CIhmAppFormQtCpp::on_timerLcd()
{
    if(m_affLibre)
        m_aff->afficherMesures(m_shm->lire(0),m_shm->lire(1), m_shm->lire(2));
}

void CIhmAppFormQtCpp::setIhm(bool t)
{
    ui->leInterBdd->setEnabled(t);
    ui->leInterCapt->setEnabled(t);
    ui->leInterPeriph->setEnabled(t);
    ui->leInterServ->setEnabled(t);

    ui->cbBits->setEnabled(t);
    ui->cbParite->setEnabled(t);
    ui->cbPorts->setEnabled(t);
    ui->cbStop->setEnabled(t);
    ui->cbVitesse->setEnabled(t);

    ui->leAdrServ->setEnabled(t);
    ui->lePortServ->setEnabled(t);

    ui->leAdrSgbd->setEnabled(t);
    ui->leNomBdd->setEnabled(t);
    ui->lePassSgbd->setEnabled(t);
    ui->leUserSgbd->setEnabled(t);

    ui->leSeuilHumI2c->setEnabled(t);
    ui->leSeuilTempI2c->setEnabled(t);
    ui->leSeuilTempSpi->setEnabled(t);
}

void CIhmAppFormQtCpp::on_pbId_clicked()
{
    /*
    quint8 id=m_thSpi->getManufacturer();
    unsigned char trame[5];
    int res;
    trame[0] = 0x03;
    trame[1] = 0;
    res = m_tc72->SpiOpenPort(0);
    if (res<0)
        emit sigErreur("ERREUR OpenPort SPIioctl");
    res = m_tc72->SpiWriteAndRead(0, trame, 1);
    if (res<0)
        emit sigErreur("ERREUR WriteAndRead SPIioctl");
    ui->teTexte->append(QString::number(trame[0],16));
    */
}

void CIhmAppFormQtCpp::on_pbLcd_clicked()
{
    if (m_affLibre) {
        m_affLibre = false;
        thAff = new QThread();
        m_aff->moveToThread(thAff);
        connect(thAff, SIGNAL(started()), m_aff, SLOT(sequenceBienvenue()));
        connect(m_aff, SIGNAL(workFinished()), thAff, SLOT(quit()));
        connect(thAff, SIGNAL(finished()), thAff, SLOT(deleteLater()));
        connect(thAff, SIGNAL(finished()), this, SLOT(affLibre()));
        if (m_interLcd->isActive()) {
            m_interLcd->stop();
            connect(thAff, SIGNAL(finished()), m_interLcd, SLOT(start()));
        } // if isactive
        thAff->start();
    } // if libre
}

void CIhmAppFormQtCpp::affLibre()
{
    m_affLibre = true;
    delete thAff;
}
