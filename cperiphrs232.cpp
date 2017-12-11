#include "cperiphrs232.h"

CPeriphRs232::CPeriphRs232(QObject *parent, QString nomPort)
{
    m_parent = parent;
    // initialisation de la mémoire partagée
    mShm = new QSharedMemory(KEY,this);
    mShm->attach();   // tentative de s'attacher
    if (!mShm->isAttached()) {   // si existe pas alors création
        QString mess="CPeriphRs232::CPeriphRs232 Erreur de création de la mémoire partagée.";
        emit sigErreur(mess);
      return;
    } // if isattached
    rs = new CRs232c(this, "/dev"+nomPort);
    connect(rs, SIGNAL(sigData(QByteArray)), this, SLOT(onData(QByteArray)));
    connect(rs, SIGNAL(sigErreur(QSerialPort::SerialPortError)), this, SLOT(onErreur(QSerialPort::SerialPortError)));
    qDebug() << "Objet CPeriphRs232 créé !";
}

CPeriphRs232::~CPeriphRs232()
{
    delete rs;
    mShm->detach();
    delete mShm;
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
    return rs->ecrire(mess.toStdString().c_str(), mess.size());
}

void CPeriphRs232::onErreur(QSerialPort::SerialPortError err)
{
    QString mess="CPeriphRs232::onErreur ERREUR port série "+err;
    emit sigErreur(mess);
}

void CPeriphRs232::onData(QByteArray data)
{
    emit sigData(QString(data));
}
