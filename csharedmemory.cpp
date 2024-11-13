#include "csharedmemory.h"

CSharedMemory::CSharedMemory(QObject *parent, int size) :
    QSharedMemory(parent)
{
    _parent = parent;
    setKey(KEY);
    _taille = size;
    _adrBase = NULL;
    qDebug() << "Objet CSharedMemory créé par " << _parent->thread();
}

CSharedMemory::~CSharedMemory()
{
    detach();
    qDebug() << "Objet CSharedMemory détruit par " << _parent->thread();
}

int CSharedMemory::attacherOuCreer()
{
    int res;

    attach();   // tentative de s'attacher
    if (!isAttached()) {   // si existe pas alors création
         res = create(_taille);   // on réserve la place
         if (!res) {
              QString mess="CSharedMemory::attacherOuCreer Erreur de création de la mémoire partagée.";
              emit sig_erreur(mess);
              return ERREUR;
         } // if res
    } // if isattached
    attach();
    _adrBase = (float *)data();
    return 0;
}

int CSharedMemory::attacherSeulement()
{
    attach();   // tentative de s'attacher
    if (!isAttached()) {   // si existe pas
        QString mess="CSharedMemory::attacherSeulement Erreur de création de la mémoire partagée.";
      emit sig_erreur(mess);
      return ERREUR;
    } // if isattached
    _adrBase = (float *)data();
    return 0;
}

int CSharedMemory::ecrire(int no, float mesure)
{
    if ( (no<0) && (no>2) ) {
        QString mess="CSharedMemory::ecrire ERREUR, indice de la mesure incorrecte.";
        emit sig_erreur(mess);
        return ERREUR;
    } // if no
    if (!isAttached()) {   // si existe pas
        QString mess="CSharedMemory::ecrire Erreur mémoire partagée non attachée.";
        emit sig_erreur(mess);
        return ERREUR;
    } // if isattached
    _adrBase[no] = mesure;
    return 0;
}

float CSharedMemory::lire(int no)
{
    if ( (no<0) && (no>2) ) {
        QString mess="CSharedMemory::lire ERREUR, indice de la mesure incorrecte.";
        emit sig_erreur(mess);
        return ERREUR;
    } // if no
    if (!isAttached()) {   // si existe pas alors création
        QString mess="CSharedMemory::lire Erreur mémoire partagée non attachée. ";
      emit sig_erreur(mess);
      return ERREUR;
    } // if isattached
    return _adrBase[no];
}
