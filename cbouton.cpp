#include "cbouton.h"

CBouton::CBouton(QObject *parent, int noGpio) :
    QThread(parent)
{
    gpio = new CGpio(noGpio, OUT);
    mValMem = false;
}

CBouton::~CBouton()
{
    delete gpio;
}

void CBouton::run()
{
    int val;
    bool etat;

    while(1) {
        val = gpio->lire();
        etat = (val!=0?false:true);  // 1 au repos
        if (etat != mValMem) {
            mValMem = etat;
            emit etatBouton(mValMem);
        } // if
        usleep(100000);
    } // wh
}
