#include "cclienttcp.h"

CClientTcp::CClientTcp(QObject *parent) :
    QObject(parent)
{
    m_sock = new QTcpSocket(this);
    connect(m_sock, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_sock, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_sock, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(m_sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    qDebug() << "Objet CClientTcp créé !";
}

CClientTcp::~CClientTcp()
{
    if (m_sock->isOpen())
        m_sock->close();
    delete m_sock;
    qDebug() << "Objet CClientTcp détruit !";
}

int CClientTcp::emettre(QString mess)
{
    int nb = m_sock->write(mess.toStdString().c_str());
    if (nb == -1)
        qDebug() << "CClientTcp::emettre Erreur écriture.";
    return nb;
}

int CClientTcp::connecter(QString adr, QString port)
{
    m_sock->connectToHost(adr, port.toUShort(), QIODevice::ReadWrite);
    bool res = m_sock->isOpen();
    if (!res)
        qDebug() << "CClientTcp::connecter Erreur";
    return res;
}

void CClientTcp::deconnecter()
{
    m_sock->close();
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
    //int nb = m_sock->bytesAvailable();
//    qDebug() << nb << " octets à lire : ";

    QByteArray data;
    data = m_sock->readAll();
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
