#include "cled.h"

CLed::CLed(QObject *parent, int noGpio) : QObject(parent)
{
    m_gpio = new CGpio(this, noGpio, OUT);
    connect(m_gpio, SIGNAL(sigErreur(QString)), this, SLOT(onErreur(QString)));
    qDebug() << "Objet CLed créé !";
}

CLed::~CLed()
{
    delete m_gpio;
    qDebug() << "Objet CLed détruit !";
}

int CLed::switchOn()
{
    int res;
    res = m_gpio->ecrire(SWITCH_ON);
    return res;
}

int CLed::switchOff()
{
    int res;
    res = m_gpio->ecrire(SWITCH_OFF);
    return res;
}

void CLed::onErreur(QString mess)
{
    emit sigErreur(mess);
}
