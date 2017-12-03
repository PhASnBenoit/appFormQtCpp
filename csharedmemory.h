#ifndef CSHAREDMEMORY_H
#define CSHAREDMEMORY_H

#include <QSharedMemory>
#include "global.h"

// définition de la mémoire partagée
typedef struct {
    float temp_TC72;
    float temp_SHT20;
    float hum_SHT20;
} T_SHM_DATA;

class CSharedMemory : public QSharedMemory
{
    Q_OBJECT

public:
    explicit CSharedMemory(QObject *parent = 0, int size = 10);
    ~CSharedMemory();
    int attacherOuCreer();
    int attacherSeulement();
    int ecrire(int no, float mesure);
    float lire(int no);

private:
    int m_taille;
    float *m_adrBase;

signals:
    void sigErreur(QString mess);

public slots:

};

#endif // CSHAREDMEMORY_H
