#include "cled.h"

CLed::CLed(QObject *parent, int noGpio) : QObject(parent)
{
    _gpio27 = new CGpio2024(this, noGpio, "gpiochip0");
    qDebug() << "Objet CLed créé !";
}

CLed::~CLed()
{
    delete _gpio27;
    qDebug() << "Objet CLed détruit !";
}

int CLed::switchOn()
{
    _gpio27->setToOn();
    return 1;
}

int CLed::switchOff()
{
    _gpio27->setToOff();
    return 0;
}

void CLed::on_erreur(QString mess)
{
    emit sig_erreur(mess);
}
