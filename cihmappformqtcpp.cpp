#include "cihmappformqtcpp.h"
#include "ui_cihmappformqtcpp.h"

CIhmAppFormQtCpp::CIhmAppFormQtCpp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CIhmAppFormQtCpp)
{
    ui->setupUi(this);
    bdd = QSqlDatabase::addDatabase("QMYSQL");
    if (!bdd.isValid()) {
        emit erreur("Driver BDD non reconnu !");
    } else {
        QMessageBox::warning(this, "BDD !", "Driver BDD OK");
    } // else
}

CIhmAppFormQtCpp::~CIhmAppFormQtCpp()
{
    delete ui;
}

void CIhmAppFormQtCpp::on_pbStartStop_clicked()
{
   int etat;
   if (ui->pbStartStop->text() == "Start acquisition") etat = 1; else etat = 0;

   switch(etat) {
   case 1: // start acquisition
       // ouverture de la base de données
       bdd.setHostName(ui->leAdrSgbd->text());
       bdd.setDatabaseName(ui->leNomBdd->text());
       bdd.setUserName(ui->leUserSgbd->text());
       bdd.setPassword(ui->lePassSgbd->text());
       bool ok = bdd.open();
       if (!ok) {
           erreur("Ouverture de la BDD impossible !");
           return;
       } // if ok

       // connexion au serveur réseau

       // initialisation de la mémoire partagée
       shm = new QSharedMemory("./cihmappformqtcpp.h",this);
       ui->pbStartStop->setText("Stop acquisition");
       break;
   case 0: // stop acquisition
       ui->pbStartStop->setText("Start acquisition");
   default:
       break;
   } // sw
}

void CIhmAppFormQtCpp::on_Erreur(QString mess)
{
    QMessageBox::warning(this, "Erreur !", mess);
}
