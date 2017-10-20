#include "cled.h"

CLed::CLed(QObject *parent, int noGpio) : QObject(parent)
{
    gpio = new CGpio(noGpio, OUT);
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
