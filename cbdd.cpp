#include "cbdd.h"

CBdd::CBdd(QObject *parent) : QObject(parent)
{
    m_bdd = QSqlDatabase::addDatabase("QMYSQL");
    if (!m_bdd.isValid()) {
        emit sigErreur("CBdd::CBdd Driver BDD non reconnu !");
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
    m_bdd.setHostName(adr);
    m_bdd.setDatabaseName(NomBdd);
    m_bdd.setUserName(nomUser);
    m_bdd.setPassword(mdp);
    bool ok = m_bdd.open();
    if (!ok)
        emit sigErreur("CBdd::connecter Impossible d'ouvrir la BDD !");
    return ok;
}

void CBdd::onErreur(QString mess)
{
    emit sigErreur(mess);
}
