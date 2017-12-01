#include "ccapteurspitc72.h"

CCapteurSpiTc72::CCapteurSpiTc72(QObject *parent, int inter) :
    QThread(parent)
{
    mShm = new CSharedMemory(this, 0);
    mShm->attacherSeulement();
    mIntervale = inter;
}

CCapteurSpiTc72::~CCapteurSpiTc72()
{

}

void CCapteurSpiTc72::onErreur(QString mess)
{
   emit sigErreur(mess);
}
