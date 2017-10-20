#ifndef CSHAREDMEMORY_H
#define CSHAREDMEMORY_H

#include <QSharedMemory>
#include "global.h"

class CSharedMemory : public QSharedMemory
{
    Q_OBJECT
public:
    explicit CSharedMemory(QObject *parent = 0, int size = 4000);
    ~CSharedMemory();
    int attacherOuCreer();
    int attacherSeulement();
    int ecrire(int no, float mesure);
    float lire(int no);

private:
    int mTaille;
    float *mAdrBase;

signals:
    void erreur(QString mess);

public slots:

};

#endif // CSHAREDMEMORY_H
