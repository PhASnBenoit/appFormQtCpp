#ifndef CCAPTEURTEMPSPI_H
#define CCAPTEURTEMPSPI_H

#include <QThread>
#include "csharedmemory.h"
#include "global.h"

class CCapteurTempSpi : public QThread
{
    Q_OBJECT

public:
    explicit CCapteurTempSpi(QObject *parent = 0, int inter = 10000);
    ~CCapteurTempSpi();

private:
    CSharedMemory *mShm;
    int mIntervale;

signals:
    void erreur(QString mess);

public slots:

};

#endif // CCAPTEURTEMPSPI_H
