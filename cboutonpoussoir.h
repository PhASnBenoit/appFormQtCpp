#ifndef CBOUTONPOUSSOIR_H
#define CBOUTONPOUSSOIR_H

#include <QDebug>
#include <QThread>
#include "../biblis/cgpio2024.h"

class CBoutonPoussoir : public QObject
{
    Q_OBJECT
public:
    explicit CBoutonPoussoir(QObject *parent = nullptr, int noGpio = 22);
    ~CBoutonPoussoir();
    bool _fin;

private:
    CGpio2024 *_gpio;
    int _valMem;  // état mémoire

signals:
    void sig_etatBouton(bool etat);
    void sig_erreur(QString mess);

public slots:
    void on_go();

private slots:
    void on_erreur(QString mess);

};

#endif // CBOUTONPOUSSOIR_H
