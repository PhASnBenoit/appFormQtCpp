#include "cbouton.h"

CBouton::CBouton(QObject *parent, int noGpio) :
    QThread(parent)
{
    gpio = new CGpio(noGpio, IN);
    connect(gpio, SIGNAL(sigErreur(QString)), this, SLOT(onErreur(QString)));
    mValMem = false;
}

CBouton::~CBouton()
{
    delete gpio;
}

void CBouton::run()
{
    int etat;

    while(1) {
        etat = gpio->lire();
        if (etat != mValMem) {
            mValMem = etat;
            emit sigEtatBouton(mValMem);
            qDebug() << "etat bouton : " << mValMem;
        } // if
        usleep(50000);
    } // wh
}

void CBouton::onErreur(QString mess)
{
    emit sigErreur(mess);
}
