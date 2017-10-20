#include "ccapteurtempspi.h"

CCapteurTempSpi::CCapteurTempSpi(QObject *parent, int inter) :
    QThread(parent)
{
    mShm = new CSharedMemory(this, 0);
    mShm->attacherSeulement();
    mIntervale = inter;
}

CCapteurTempSpi::~CCapteurTempSpi()
{

}
