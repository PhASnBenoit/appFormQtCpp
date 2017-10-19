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
    } else {
        QMessageBox::warning(this, "BDD !", "Driver BDD OK");
    } // else

    // LED
    led = new CLed(this, GPIO27);

    // lance thread CBouton
    thread_bt = new CBouton(this, GPIO22);
    thread_bt->start();

    thI2c = NULL;
    tSpi = NULL;

    interEcran = new QTimer(this);
    interServeur = new QTimer(this);
    interSgbd = new QTimer(this);
}

CIhmAppFormQtCpp::~CIhmAppFormQtCpp()
{
    delete interEcran;
    delete interServeur;
    delete interSgbd;

    delete thread_bt;
    delete led;

    if (thI2c) delete thI2c;
    if (tSpi) delete tSpi;
    if (shm) delete shm;
    delete ui;  // toujours en dernier
}

void CIhmAppFormQtCpp::on_pbStartStop_clicked()
{
   bool ok;
   int etat;
   if (ui->pbStartStop->text() == "Start acquisition") etat = 1; else etat = 2;

   switch(etat) {
   case 1: // start acquisition
       setIhm(false);
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

       // initialisation de la mémoire partagée
       shm = new QSharedMemory("./cihmappformqtcpp.h",this);
       ui->pbStartStop->setText("Stop acquisition");

       // lance les thread capteurs
       thI2c = new CCapteurTempHumI2c(this);
       thI2c->start();
       tSpi = new CCapteurTempSpi(this);
       tSpi->start();

       // ouvrir le port série avec le terminal
       periph = new CPeriphRs232(this, "/dev/"+ui->cbPorts->currentText());
       periph->start();

       // lance les timers d'acquisition
       interEcran->start(ui->leInterEcran->text().toInt());
       interServeur->start(ui->leInterServ->text().toInt());
       interSgbd->start(ui->leInterBdd->text().toInt());

       // verrouille l'IHM
       setIhm(false);  // verrouille l'IHM quand acquisition

       break;

   default: // stop acquisition

       interEcran->stop();
       interServeur->stop();
       interSgbd->stop();
       delete periph;
       delete thI2c;
       delete tSpi;
       delete shm;
       ui->pbStartStop->setText("Start acquisition");
       setIhm(true);
       break;
   } // sw
}

void CIhmAppFormQtCpp::on_Erreur(QString mess)
{
    QMessageBox::warning(this, "Erreur !", mess);
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
    ui->leInterEcran->setEnabled(t);
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
