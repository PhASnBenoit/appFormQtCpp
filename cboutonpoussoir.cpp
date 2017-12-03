#include "cboutonpoussoir.h"

CBoutonPoussoir::CBoutonPoussoir(QObject *parent, int noGpio) :
    QThread(parent)
{
    gpio = new CGpio(noGpio, IN);
    connect(gpio, SIGNAL(sigErreur(QString)), this, SLOT(onErreur(QString)));
    m_valMem = false;
}

CBoutonPoussoir::~CBoutonPoussoir()
{
    delete gpio;
}

void CBoutonPoussoir::run()
{
    int etat;

    while(1) {
        etat = gpio->lire();
        if (etat != m_valMem) {
            m_valMem = etat;
            emit sigEtatBouton(m_valMem);
            qDebug() << "etat bouton : " << m_valMem;
        } // if
        usleep(50000);
    } // wh
}

void CBoutonPoussoir::onErreur(QString mess)
{
    emit sigErreur(mess);
}
