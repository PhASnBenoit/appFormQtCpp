#include "cboutonpoussoir.h"

CBoutonPoussoir::CBoutonPoussoir(QObject *parent, int noGpio)
{
    _gpio = new CGpio2024(this, noGpio, "gpiochip0");
    //connect(_gpio, SIGNAL(sigErreur(QString)), this, SLOT(onErreur(QString)));
    _valMem = false;
    _fin=false;
    qDebug() << "Démarrage de l'objet CBoutonPoussoir";
}

CBoutonPoussoir::~CBoutonPoussoir()
{
    delete _gpio;
    qDebug() << "Objet CBoutonPoussoir détruit !";
}

void CBoutonPoussoir::on_go()
{
    int etat;

    while(!_fin) {
        etat = _gpio->getGpio();
        if (etat != _valMem) {
            _valMem = etat;
            emit sig_etatBouton(_valMem);
            qDebug() << "etat bouton : " << _valMem;
        } // if
        QThread::usleep(50000);
    } // wh
}

void CBoutonPoussoir::on_erreur(QString mess)
{
    emit sig_erreur(mess);
}
