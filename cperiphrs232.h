#ifndef CPERIPHRS232_H
#define CPERIPHRS232_H


#include <QObject>
#include <QDebug>
#include <QSerialPort>  // ne pas oublier d'ajouter QT+=serialport dans .pro
#include <QSerialPortInfo>
#include <QSharedMemory>
#include "global.h"
#include "/home/pi/devQt/biblis/crs232c.h"

class CPeriphRs232: public QObject
{
    Q_OBJECT

public:
    explicit CPeriphRs232(QObject *parent = 0, QString nomPort = "ttyUSB0");
    ~CPeriphRs232();
    static QStringList portsDisponibles();
    int emettre(QString mess);

private:
    QSharedMemory *mShm;
    CRs232c *rs;
    QObject *m_parent;

signals:
    void sigErreur(QString mess);
    void sigData(QString data);

private slots:
    void onErreur(QSerialPort::SerialPortError err);
    void onData(QByteArray data);
};

#endif // CPERIPHRS232_H
