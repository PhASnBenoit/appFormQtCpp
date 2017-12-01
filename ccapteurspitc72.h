#ifndef CCAPTEURSPITC72_H
#define CCAPTEURSPITC72_H

#include <QThread>
#include "csharedmemory.h"
#include "global.h"

class CCapteurSpiTc72 : public QThread
{
    Q_OBJECT

public:
    explicit CCapteurSpiTc72(QObject *parent = 0, int inter = 10000);
    ~CCapteurSpiTc72();

private:
    CSharedMemory *mShm;
    int mIntervale;

signals:
    void sigErreur(QString mess);

private slots:
    void onErreur(QString mess);

};

#endif // CCAPTEURTEMPSPI_H
