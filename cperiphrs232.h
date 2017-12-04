#ifndef CPERIPHRS232_H
#define CPERIPHRS232_H

#include <QThread>
#include <QDebug>
#include <QSerialPort>  // ne pas oublier d'ajouter QT+=serialport dans .pro
#include <QSharedMemory>
#include "global.h"

class CPeriphRs232 : public QThread
{
    Q_OBJECT
public:
    explicit CPeriphRs232(QObject *parent = 0, QString port = "/dev/USB0", int inter = 10000);
    ~CPeriphRs232();

private:
    int mIntervale;
    QSharedMemory *mShm;
    void run();

signals:
    void sigErreur(QString mess);

private slots:
    void onErreur(QString mess);

};

#endif // CPERIPHRS232_H
