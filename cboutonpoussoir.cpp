#include "cboutonpoussoir.h"

CBoutonPoussoir::CBoutonPoussoir(QObject *parent, int noGpio) :
    QThread(parent)
{
    m_gpio = new CGpio(this, noGpio, IN);
    connect(m_gpio, SIGNAL(sigErreur(QString)), this, SLOT(onErreur(QString)));
    m_valMem = false;
    m_fin=false;
    qDebug() << "Démarrage de l'objet CBoutonPoussoir";
}

CBoutonPoussoir::~CBoutonPoussoir()
{
    delete m_gpio;
    qDebug() << "Objet CBoutonPoussoir détruit !";
}

void CBoutonPoussoir::run()
{
    int etat;

    while(!m_fin) {
        etat = m_gpio->lire();
        if (etat != m_valMem) {
            m_valMem = etat;
            emit sigEtatBouton(m_valMem);
//            qDebug() << "etat bouton : " << m_valMem;
        } // if
        usleep(50000);
    } // wh
}

void CBoutonPoussoir::onErreur(QString mess)
{
    emit sigErreur(mess);
}
