#include "cclienttcp.h"

CClientTcp::CClientTcp(QObject *parent) :
    QObject(parent)
{
    _sock = new QTcpSocket(this);
    connect(_sock, SIGNAL(connected()), this, SLOT(on_connected()));
    connect(_sock, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
    connect(_sock, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
    connect(_sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(on_socketError(QAbstractSocket::SocketError)));
    qDebug() << "Objet CClientTcp créé !";
}

CClientTcp::~CClientTcp()
{
    if (_sock->isOpen())
        _sock->close();
    delete _sock;
    qDebug() << "Objet CClientTcp détruit !";
}

int CClientTcp::emettre(QString mess)
{
    int nb = _sock->write(mess.toStdString().c_str());
    if (nb == -1)
        qDebug() << "CClientTcp::emettre Erreur écriture.";
    return nb;
}

int CClientTcp::connecter(QString adr, QString port)
{
    _sock->connectToHost(adr, port.toUShort(), QIODevice::ReadWrite);
    bool res = _sock->isOpen();
    if (!res)
        qDebug() << "CClientTcp::connecter Erreur";
    return res;
}

void CClientTcp::deconnecter()
{
    _sock->close();
}

/////////////  SLOTs /////////////////////////////////////

void CClientTcp::on_connected()
{
//    qDebug() << "Client connecté.";
    emit sig_evenement("CON"); // communication avec IHM
}

void CClientTcp::on_disconnected()
{
//    qDebug() << "Client déconnecté.";
    emit sig_evenement("DEC"); // communication avec IHM
}

void CClientTcp::on_readyRead()
{
    //int nb = m_sock->bytesAvailable();
//    qDebug() << nb << " octets à lire : ";

    QByteArray data;
    data = _sock->readAll();
//    qDebug() << "CClientTcp::onReadyRead " << data;
    emit sig_data(QString(data));  // transmission à l'IHM par signal
}

void CClientTcp::on_socketError(QAbstractSocket::SocketError err)
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
    emit sig_erreur(mess);
}
