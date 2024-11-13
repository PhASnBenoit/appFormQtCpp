#include "cperiphrs232.h"

CPeriphRs232::CPeriphRs232(QObject *parent, QString nomPort)
{
    _parent = parent;
    _rs = new CRs232c(this, nomPort);
    connect(_rs, SIGNAL(sig_data(QByteArray)), this, SLOT(on_data(QByteArray)));
    connect(_rs, SIGNAL(sig_erreur(QSerialPort::SerialPortError)), this, SLOT(on_erreur(QSerialPort::SerialPortError)));
    qDebug() << "Objet CPeriphRs232 créé !";
}

CPeriphRs232::~CPeriphRs232()
{
    delete _rs;
    qDebug() << "Objet CPeriphRs232 détruit !";
}

QStringList CPeriphRs232::portsDisponibles()
{
    QStringList stringList;
    QList<QSerialPortInfo> spi;
    spi = QSerialPortInfo::availablePorts();
    for (int i=0 ; i<spi.size() ; i++) {
        QString str = spi.at(i).portName();
        stringList.append(str);
    } // for
    return stringList;
}

int CPeriphRs232::emettre(QString mess)
{
    return _rs->ecrire(mess.toStdString().c_str(), mess.size());
}

int CPeriphRs232::initialiser(QString vitesse, QString data, QString parity, QString nbStop, QString flow)
{
    QSerialPort::BaudRate vit=(QSerialPort::BaudRate)vitesse.toInt();
    QSerialPort::DataBits dat=(QSerialPort::DataBits)data.toInt();
    QSerialPort::StopBits nbS=(QSerialPort::StopBits)nbStop.toInt();
    QSerialPort::FlowControl fl=(QSerialPort::FlowControl)flow.toInt();
    QSerialPort::Parity par=QSerialPort::NoParity;
    if (parity == "Paire")
        par = QSerialPort::EvenParity;
    if (parity == "Impaire")
        par = QSerialPort::OddParity;
    _rs->ouvrirPort();
    return _rs->initialiser(vit, dat, par, nbS, fl);
}

void CPeriphRs232::on_erreur(QSerialPort::SerialPortError err)
{
    QString mess;
    switch (err) {
    case QSerialPort::NotOpen:
        mess="CPeriphRs232::onErreur impossible ouvrir port série";
        break;
    case QSerialPort::WriteError:
        mess="CPeriphRs232::onErreur impossible d'écrire";
        break;
    case QSerialPort::ReadError:
        mess="CPeriphRs232::onErreur impossible de lire";
        break;
    default:
        mess="CPeriphRs232::onErreur ERREUR non déterminée";
    } // sw
    emit sig_erreur(mess);
}

void CPeriphRs232::on_data(QByteArray data)
{
    emit sig_data(QString(data));
}
