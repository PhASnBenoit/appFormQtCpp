#include "cperiphrs232.h"

CPeriphRs232::CPeriphRs232(QObject *parent, QString port, int inter) :
    QThread(parent)
{
    mIntervale = inter;
    // initialisation de la mémoire partagée
    mShm = new QSharedMemory(KEY,this);
    mShm->attach();   // tentative de s'attacher
    if (!mShm->isAttached()) {   // si existe pas alors création
      emit erreur("Erreur de création de la mémoire partagée.");
      return;
    } // if isattached
}

CPeriphRs232::~CPeriphRs232()
{
    mShm->detach();
    delete mShm;
}

void CPeriphRs232::run()
{
    while(1) {

    } // wh
}
