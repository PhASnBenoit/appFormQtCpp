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
    bdd = QSqlDatabase::addDatabase("QMYSQL");
    if (!bdd.isValid()) {
        emit sigErreur("CIhmAppFormQtCpp::CIhmAppFormQtCpp Driver BDD non reconnu !");
    }

    // initialisation de la mémoire partagée
    mShm = new CSharedMemory(this, NBMESURES*sizeof(float));
    mShm->attacherOuCreer();

    // intanciation de l'objet LED
    led = new CLed(this, GPIO_LED);

    // lance thread CBouton
    thBt = new CBouton(this, GPIO_BOUTON);
    connect(thBt, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
    connect(thBt, SIGNAL(sigEtatBouton(bool)), this, SLOT(on_etatBouton(bool)));
    thBt->start();

    thI2c = NULL;
    thSpi = NULL;

    interServeur = new QTimer(this);
    interSgbd = new QTimer(this);
}

CIhmAppFormQtCpp::~CIhmAppFormQtCpp()
{
    delete interServeur;
    delete interSgbd;

    // arrêter avant le thread
    delete thBt;
    delete led;

    if (thI2c) delete thI2c;
    if (thSpi) delete thSpi;
    delete mShm;
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
       bdd.setHostName(ui->leAdrSgbd->text());
       bdd.setDatabaseName(ui->leNomBdd->text());
       bdd.setUserName(ui->leUserSgbd->text());
       bdd.setPassword(ui->lePassSgbd->text());
       ok = bdd.open();
       if (!ok) {
           emit sigErreur("CIhmAppFormQtCpp::on_pbStartStop_clicked Ouverture de la BDD impossible !");
           return;
       } // if ok

       // connexion au serveur réseau


       // lance les thread capteurs
       thI2c = new CCapteurI2cSht20(this);
       connect(thI2c, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       thI2c->start();
       thSpi = new CCapteurSpiTc72(this);
       connect(thSpi, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       thSpi->start();

       // ouvrir le port série avec le terminal
       thPeriph = new CPeriphRs232(this, "/dev/"+ui->cbPorts->currentText(), ui->leInterPeriph->text().toInt()*1000);
       connect(thPeriph, SIGNAL(sigErreur(QString)), this, SLOT(on_Erreur(QString)));
       thPeriph->start();

       // lance les timers d'acquisition
       interServeur->start(ui->leInterServ->text().toInt()*1000);
       interSgbd->start(ui->leInterBdd->text().toInt()*1000);

       // verrouille l'IHM
       setIhm(false);  // verrouille l'IHM quand acquisition

       break;

   default: // stop acquisition

       interServeur->stop();
       delete interServeur;
       interSgbd->stop();
       delete interSgbd;
       delete thPeriph;
       delete thI2c;
       delete thSpi;
       delete mShm;
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
        led->switchOn();
        break;
    default:  // éteindre
        ui->laRouge->setVisible(false);
        ui->laNoir->setVisible(true);
        ui->pbOnOffLed->setText("Allumer");
        led->switchOff();
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
