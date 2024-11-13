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
    QSqlDatabase _bdd;

signals:
    void sig_erreur(QString mess);

private slots:
    void on_erreur(QString mess);
};

#endif // CBDD_H
