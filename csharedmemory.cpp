#include "csharedmemory.h"

CSharedMemory::CSharedMemory(QObject *parent, int size) :
    QSharedMemory(parent)
{
    setKey(KEY);
    mTaille = size;
    mAdrBase = NULL;
}

CSharedMemory::~CSharedMemory()
{
    detach();
}

int CSharedMemory::attacherOuCreer()
{
    int res;

    attach();   // tentative de s'attacher
    if (!isAttached()) {   // si existe pas alors création
         res = create(mTaille);   // on réserve pour 3 mesures
         if (!res) {
              QString mess="CSharedMemory::attacherOuCreer Erreur de création de la mémoire partagée.";
              emit sigErreur(mess);
              return ERREUR;
         } // if res
    } // if isattached
    attach();
    mAdrBase = (float *)data();
    return 0;
}

int CSharedMemory::attacherSeulement()
{
    attach();   // tentative de s'attacher
    if (!isAttached()) {   // si existe pas alors création
        QString mess="CSharedMemory::attacherSeulement Erreur de création de la mémoire partagée.";
      emit sigErreur(mess);
      return ERREUR;
    } // if isattached
    mAdrBase = (float *)data();
    return 0;
}

int CSharedMemory::ecrire(int no, float mesure)
{
    if ( (no<0) && (no>2) ) {
        QString mess="CSharedMemory::ecrire ERREUR, indice de la mesure incorrecte.";
        emit sigErreur(mess);
        return ERREUR;
    } // if no
    if (!isAttached()) {   // si existe pas alors création
        QString mess="CSharedMemory::ecrire Erreur mémoire partagée non attachée.";
        emit sigErreur(mess);
        return ERREUR;
    } // if isattached
    mAdrBase[no] = mesure;
    return 0;

}

float CSharedMemory::lire(int no)
{
    if ( (no<0) && (no>2) ) {
        QString mess="CSharedMemory::lire ERREUR, indice de la mesure incorrecte.";
        emit sigErreur(mess);
        return ERREUR;
    } // if no
    if (!isAttached()) {   // si existe pas alors création
        QString mess="CSharedMemory::lire Erreur mémoire partagée non attachée. ";
      emit sigErreur(mess);
      return ERREUR;
    } // if isattached
    return mAdrBase[no];
}
