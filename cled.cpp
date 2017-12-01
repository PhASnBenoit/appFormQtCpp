#include "cled.h"

CLed::CLed(QObject *parent, int noGpio) : QObject(parent)
{
    gpio = new CGpio(noGpio, OUT);
    connect(gpio, SIGNAL(sigErreur(QString)), this, SLOT(onErreur(QString)));
}

CLed::~CLed()
{
    delete gpio;
}

int CLed::switchOn()
{
    int res;
    res = gpio->ecrire(SWITCH_ON);
    return res;
}

int CLed::switchOff()
{
    int res;
    res = gpio->ecrire(SWITCH_OFF);
    return res;
}

void CLed::onErreur(QString mess)
{
    emit sigErreur(mess);
}
