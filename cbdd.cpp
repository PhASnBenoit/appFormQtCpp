#include "cbdd.h"

CBdd::CBdd(QObject *parent) : QObject(parent)
{
    _bdd = QSqlDatabase::addDatabase("QMYSQL");
    if (!_bdd.isValid()) {
        emit sig_erreur("CBdd::CBdd Driver BDD non reconnu !");
        qDebug() << "Objet CBdd driver non reconnu !";
    } // if bdd
    qDebug() << "Objet CBdd créé !";
}

int CBdd::sauverMesure(int no, float valeur)
{
    QSqlQuery query;
    query.prepare("UPDATE def_mesures SET val_inst=:valeur WHERE no=:no");
    query.bindValue(":no", no);
    query.bindValue(":valeur", valeur);
    return query.exec();
}

int CBdd::connecter(QString adr, QString NomBdd, QString nomUser, QString mdp)
{
    _bdd.setHostName(adr);
    _bdd.setDatabaseName(NomBdd);
    _bdd.setUserName(nomUser);
    _bdd.setPassword(mdp);
    bool ok = _bdd.open();
    if (!ok)
        emit sig_erreur("CBdd::connecter Impossible d'ouvrir la BDD !");
    return ok;
}

void CBdd::on_erreur(QString mess)
{
    emit sig_erreur(mess);
}
