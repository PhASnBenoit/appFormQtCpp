#ifndef CCAPTEURI2CSHT20_H
#define CCAPTEURI2CSHT20_H

#include <QThread>
#include "global.h"
#include "csharedmemory.h"

class CCapteurI2cSht20 : public QThread
{
    Q_OBJECT

public:
    explicit CCapteurI2cSht20(QObject *parent = 0, int inter = 10000);
    ~CCapteurI2cSht20();

private:
    CSharedMemory *mShm;
    int mIntervale;

signals:
    void sigErreur(QString mess);

private slots:
    void onErreur(QString mess);

};

#endif // CCAPTEURTEMPHUMI2C_H
