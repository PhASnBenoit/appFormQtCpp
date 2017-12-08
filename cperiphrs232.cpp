#include "cperiphrs232.h"

CPeriphRs232::CPeriphRs232(QObject *parent, QString port, int inter) :
    QThread(parent)
{
    mIntervale = inter;
    // initialisation de la mémoire partagée
    mShm = new QSharedMemory(KEY,this);
    mShm->attach();   // tentative de s'attacher
    if (!mShm->isAttached()) {   // si existe pas alors création
        QString mess="CPeriphRs232::CPeriphRs232 Erreur de création de la mémoire partagée.";
        emit sigErreur(mess);
      return;
    } // if isattached
    qDebug() << "Objet CPeriphRs232 créé !";
}

CPeriphRs232::~CPeriphRs232()
{
    mShm->detach();
    delete mShm;
    qDebug() << "Objet CPeriphRs232 détruit !";

}

void CPeriphRs232::run()
{
    while(1) {

    } // wh
}

void CPeriphRs232::onErreur(QString mess)
{
    emit sigErreur(mess);
}
