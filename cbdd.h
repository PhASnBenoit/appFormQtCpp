#ifndef CBDD_H
#define CBDD_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

class CBdd : public QObject
{
    Q_OBJECT
public:
    explicit CBdd(QObject *parent = 0);
    int sauverMesure(int no, float valeur);
    int connecter(QString adr, QString NomBdd, QString nomUser, QString mdp);

private:
    QSqlDatabase m_bdd;


signals:
    void sigErreur(QString mess);

private slots:
    void onErreur(QString mess);
};

#endif // CBDD_H
