#include "cihmappformqtcpp.h"
#include "ui_cihmappformqtcpp.h"

CIhmAppFormQtCpp::CIhmAppFormQtCpp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CIhmAppFormQtCpp)
{
    ui->setupUi(this);
    setIhm(true);

    // BDD
    bdd = QSqlDatabase::addDatabase("QMYSQL");
    if (!bdd.isValid()) {
        emit erreur("Driver BDD non reconnu !");
    }

    // initialisation de la mémoire partagée
    mShm = new CSharedMemory(this, 3*sizeof(float));
    mShm->attacherOuCreer();

    // intanciation de l'objet LED
    led = new CLed(this, GPIO27);

    // lance thread CBouton
    thread_bt = new CBouton(this, GPIO22);
    thread_bt->start();

    thI2c = NULL;
    tSpi = NULL;

    interServeur = new QTimer(this);
    interSgbd = new QTimer(this);
}

CIhmAppFormQtCpp::~CIhmAppFormQtCpp()
{
    delete interServeur;
    delete interSgbd;

    delete thread_bt;
    delete led;

    if (thI2c) delete thI2c;
    if (tSpi) delete tSpi;
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
           emit erreur("Ouverture de la BDD impossible !");
           return;
       } // if ok

       // connexion au serveur réseau


       // lance les thread capteurs
       thI2c = new CCapteurTempHumI2c(this);
       thI2c->start();
       tSpi = new CCapteurTempSpi(this);
       tSpi->start();

       // ouvrir le port série avec le terminal
       periph = new CPeriphRs232(this, "/dev/"+ui->cbPorts->currentText(), ui->leInterPeriph->text().toInt()*1000);
       periph->start();

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
       delete periph;
       delete thI2c;
       delete tSpi;
       delete mShm;
       ui->pbStartStop->setText("Start acquisition");
       setIhm(true);
       break;
   } // sw
}

void CIhmAppFormQtCpp::on_Erreur(QString mess)
{
    QMessageBox::warning(this, "Erreur !", mess);
}

void CIhmAppFormQtCpp::on_etatBouton(bool etat)
{
    ui->teTexte->append((etat?"Bouton relâché !":"Bouton appuyé !"));
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
