#include "cperiphrs232.h"

CPeriphRs232::CPeriphRs232(QObject *parent, QString nomPort)
{
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

void CPeriphRs232::onErreur(QString mess)
{
    emit sigErreur(mess);
}

void CPeriphRs232::onData(QByteArray data)
{
    emit sigData(QString(data));
}
