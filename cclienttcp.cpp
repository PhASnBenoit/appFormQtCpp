#include "cclienttcp.h"

CClientTcp::CClientTcp(QObject *parent) :
    QObject(parent)
{
    sock = new QTcpSocket(this);
    connect(sock, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(sock, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    qDebug() << "Objet CClientTcp créé !";
}

CClientTcp::~CClientTcp()
{
    if (sock->isOpen())
        sock->close();
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
    bool res = sock->isOpen();
    if (!res)
        qDebug() << "CClientTcp::connecter Erreur";
    return res;
}

void CClientTcp::deconnecter()
{
    sock->close();
}

/////////////  SLOTs /////////////////////////////////////

void CClientTcp::onConnected()
{
//    qDebug() << "Client connecté.";
    emit sigEvenement("CON"); // communication avec IHM
}

void CClientTcp::onDisconnected()
{
//    qDebug() << "Client déconnecté.";
    emit sigEvenement("DEC"); // communication avec IHM
}

void CClientTcp::onReadyRead()
{
    //int nb = sock->bytesAvailable();
//    qDebug() << nb << " octets à lire : ";

    QByteArray data;
    data = sock->readAll();
//    qDebug() << "CClientTcp::onReadyRead " << data;
    emit sigData(QString(data));  // transmission à l'IHM par signal
}

void CClientTcp::onSocketError(QAbstractSocket::SocketError err)
{
    QString mess="CClientTcp::onSocketError erreur !";
    switch (err) {
      case QAbstractSocket::ConnectionRefusedError:
        mess = "Connexion refusée par le serveur !";
      break;
    case QAbstractSocket::NetworkError:
        mess = "Coupure de liaison réseau !";
    break;
    default:
        mess="Erreur réseau à déterminer !";
      break;
    } // sw
//  qDebug() << mess;
    emit sigErreur(mess);
}
