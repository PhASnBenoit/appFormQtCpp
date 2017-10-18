#include "cbouton.h"

CBouton::CBouton(QObject *parent, int noGpio) :
    QThread(parent)
{
    gpio = new CGpio(22, OUT);
}

CBouton::~CBouton()
{
    delete gpio;
}
