#include "ccapteuri2csht20.h"

CCapteurI2cSht20::CCapteurI2cSht20(QObject *parent, int inter) :
    QThread(parent)
{
    mShm = new CSharedMemory(this);
    mShm->attacherSeulement();
    mIntervale = inter;
}

CCapteurI2cSht20::~CCapteurI2cSht20()
{
    delete mShm;
}

void CCapteurI2cSht20::onErreur(QString mess)
{
    emit sigErreur(mess);
}
