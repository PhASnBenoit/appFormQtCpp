#include "cclienttcp.h"

CClientTcp::CClientTcp(QObject *parent) :
    QObject(parent)
{
    sock = new QTcpSocket(this);
    connect(sock, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(sock, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
}

CClientTcp::~CClientTcp()
{
    delete sock;
    qDebug() << "Objet CClientTcp détruit !";
}

int CClientTcp::emettre(QString mess)
{
    int nb = sock->write(mess.toStdString().c_str());
    if (nb == -1)
        qDebug() << "CClientTcp::emettre Erreur écriture.";
    return nb;
}

int CClientTcp::connecter(QString adr, QString port)
{
    sock->connectToHost(adr, port.toUShort(), QIODevice::ReadWrite);
    if (!sock->isOpen())
        qDebug() << "CClientTcp::connecter Erreur";
    return 1;
}

void CClientTcp::deconnecter()
{
    sock->close();
}

/////////////  SLOTs /////////////////////////////////////

void CClientTcp::onConnected()
{
    qDebug() << "Client connecté.";
    emit sigEvenement("CON"); // communication avec IHM
}

void CClientTcp::onDisconnected()
{
    qDebug() << "Client déconnecté.";
    emit sigEvenement("DEC"); // communication avec IHM
}

void CClientTcp::onReadyRead()
{
    int nb = sock->bytesAvailable();
    qDebug() << nb << " octets à lire : ";

    QByteArray data;
    data = sock->readAll();
    qDebug() << "CClientTcp::onReadyRead " << data;
    emit sigData(QString(data));  // transmission à l'IHM par signal
}

void CClientTcp::onSocketError(QAbstractSocket::SocketError err)
{
  qDebug() << "CClientTcp::onSocketError erreur !";
  emit sigErreur(err);
}
