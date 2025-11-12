#ifndef CPERIPHRS232_H
#define CPERIPHRS232_H


#include <QObject>
#include <QDebug>
#include <QSerialPort>  // ne pas oublier d'ajouter QT+=serialport dans .pro
#include <QSerialPortInfo>
#include "global.h"
#include "../biblis/crs232c.h"

class CPeriphRs232: public QObject
{
    Q_OBJECT

public:
    explicit CPeriphRs232(QObject *parent = 0, QString nomPort = "/dev/ttyUSB0");
    ~CPeriphRs232();
    static QStringList portsDisponibles();
    int emettre(QString mess);
    int initialiser(QString vitesse, QString data,
                    QString parity, QString nbStop,
                    QString flow);

private:
    CRs232c *_rs;
    QObject *_parent;

signals:
    void sig_erreur(QString mess);
    void sig_data(QString data);

private slots:
    void on_erreur(QSerialPort::SerialPortError err);
    void on_data(QByteArray data);
};

#endif // CPERIPHRS232_H
