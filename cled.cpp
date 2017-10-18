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
    gpio->ecrire(SWITCH_ON);
    return 1;
}

int CLed::switchOff()
{
    gpio->ecrire(SWITCH_OFF);
    return 1;
}
