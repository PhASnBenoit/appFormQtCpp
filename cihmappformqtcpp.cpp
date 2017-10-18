#include "cihmappformqtcpp.h"
#include "ui_cihmappformqtcpp.h"

CIhmAppFormQtCpp::CIhmAppFormQtCpp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CIhmAppFormQtCpp)
{
    ui->setupUi(this);
    // BDD
    bdd = QSqlDatabase::addDatabase("QMYSQL");
    if (!bdd.isValid()) {
        emit erreur("Driver BDD non reconnu !");
    } else {
        QMessageBox::warning(this, "BDD !", "Driver BDD OK");
    } // else

    // LED
    led = new CLed(this, 27);  // GPIO4

    // lance thread CBouton

}

CIhmAppFormQtCpp::~CIhmAppFormQtCpp()
{
    delete led;
    if (shm) delete shm;
    delete ui;
}

void CIhmAppFormQtCpp::on_pbStartStop_clicked()
{
   bool ok;
   int etat;
   if (ui->pbStartStop->text() == "Start acquisition") etat = 1; else etat = 2;

   switch(etat) {
   case 1: // start acquisition
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
       break;

   default: // stop acquisition
       delete shm;
       ui->pbStartStop->setText("Start acquisition");
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
    case 1:
        ui->laRouge->setVisible(true);
        ui->laNoir->setVisible(false);
        ui->pbOnOffLed->setText("Eteindre");
        break;
    default:
        ui->laRouge->setVisible(false);
        ui->laNoir->setVisible(true);
        ui->pbOnOffLed->setText("Allumer");
        break;
    } // sw
}
