#ifndef CCAPTEURTEMPHUMI2C_H
#define CCAPTEURTEMPHUMI2C_H

#include <QThread>
#include "global.h"
#include "csharedmemory.h"

class CCapteurTempHumI2c : public QThread
{
    Q_OBJECT

public:
    explicit CCapteurTempHumI2c(QObject *parent = 0, int inter = 10000);
    ~CCapteurTempHumI2c();

private:
    CSharedMemory *mShm;
    int mIntervale;

signals:
    void erreur(QString mess);

public slots:

};

#endif // CCAPTEURTEMPHUMI2C_H
