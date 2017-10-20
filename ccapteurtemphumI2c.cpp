#include "ccapteurtemphumi2c.h"

CCapteurTempHumI2c::CCapteurTempHumI2c(QObject *parent, int inter) :
    QThread(parent)
{
    mShm = new CSharedMemory(this);
    mShm->attacherSeulement();
    mIntervale = inter;
}

CCapteurTempHumI2c::~CCapteurTempHumI2c()
{
    delete mShm;
}
