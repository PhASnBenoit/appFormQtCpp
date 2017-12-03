#include "cihmappformqtcpp.h"
#include "ui_cihmappformqtcpp.h"

CIhmAppFormQtCpp::CIhmAppFormQtCpp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CIhmAppFormQtCpp)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
    setIhm(true);

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

    m_thI2c = NULL;
    m_thSpi = NULL;

    m_interServeur = new QTimer(this);
    m_interSgbd = new QTimer(this);
}

CIhmAppFormQtCpp::~CIhmAppFormQtCpp()
{
    delete m_interServeur;
    delete m_interSgbd;

    // arrêter avant le thread
    delete m_thBt;
    delete m_led;

    if (m_thI2c) delete m_thI2c;
    if (m_thSpi) delete m_thSpi;
    delete m_shm;
    delete ui;  // toujours en dernier
}

void CIhmAppFormQtCpp::on_pbStartStop_clicked()
{
   bool ok;
   int etat;
   if (ui->pbStartStop->text() == "Start acquisition") etat = 1; else etat = 2;

   switch(etat) {
   case 1: // start acquisition
       // réglages IHM de départ
       setIhm(false);
       ui->pbStartStop->setText("Stop acquisition");

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

       // connexion au serveur réseau


       // lance les thread capteurs
       m_thI2c = new CCapteur_I2c_SHT20(this);
       connect(m_thI2c, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       m_thI2c->start();
       m_thSpi = new CCapteur_Spi_TC72(this, 0, 0);
       connect(m_thSpi, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       m_thSpi->start();

       // ouvrir le port série avec le terminal
       m_thPeriph = new CPeriphRs232(this, "/dev/"+ui->cbPorts->currentText(), ui->leInterPeriph->text().toInt()*1000);
       connect(m_thPeriph, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       m_thPeriph->start();

       // lance les timers d'acquisition
       m_interServeur->start(ui->leInterServ->text().toInt()*1000);
       m_interSgbd->start(ui->leInterBdd->text().toInt()*1000);

       // verrouille l'IHM
       setIhm(false);  // verrouille l'IHM quand acquisition

       break;

   default: // stop acquisition

       m_interServeur->stop();
       delete m_interServeur;
       m_interSgbd->stop();
       delete m_interSgbd;
       delete m_thPeriph;
       delete m_thI2c;
       delete m_thSpi;
       delete m_shm;
       ui->pbStartStop->setText("Start acquisition");
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
