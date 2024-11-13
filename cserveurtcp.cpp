#include "cserveurtcp.h"

CServeurTcp::CServeurTcp(QObject *parent) : QObject(parent)
{
    m_parent = parent;

    m_shm = new CSharedMemory(this);
    connect(m_shm, SIGNAL(sig_erreur(QString)), this, SLOT(on_erreur(QString)));
    m_shm->attacherSeulement();

    m_serv = new QTcpServer(this);
    connect(m_serv, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(on_socketError(QAbstractSocket::SocketError)));
    connect(m_serv, SIGNAL(newConnection()), this, SLOT(on_newConnection()));
    qDebug() << "objet CServeurTcp créé";
    m_serv->listen(QHostAddress::Any, PORT);
}

CServeurTcp::~CServeurTcp() {
    m_shm->detach();
    delete m_shm;
    delete m_serv;
    qDebug() << "objet CServeurTcp détruit";
}

void CServeurTcp::on_socketError(QAbstractSocket::SocketError err)
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

void CServeurTcp::on_newConnection()
{
    m_soc=m_serv->nextPendingConnection(); // accepte la connexion du client
    connect(m_soc, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(on_socketError(QAbstractSocket::SocketError)));
    connect(m_soc, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
    QString mess="Serveur de mesures : tapez un chiffre de 0 à 2 :";
    m_soc->write(mess.toStdString().c_str(), mess.size());
    m_soc->write("\x0d\x0a", 2);
}

void CServeurTcp::on_readyRead()
{
    QByteArray ba = m_soc->readAll(); // recoit 0 ou 1 ou 2 en ASCII
    if ( (ba.at(0)<'0') || (ba.at(0)>'2') ) {
        QString mess=" Erreur, entrez 0 ou 1 ou 2 :";
        m_soc->write(mess.toStdString().c_str(), mess.size());
        m_soc->write("\x0d\x0a", 2);
    } else {
        float valeur = m_shm->lire(ba.at(0)-0x30);
        QString strVal = QString::number(valeur, 'f', 1);
        m_soc->write("\x0d\x0a", 2);
        int nb = m_soc->write(strVal.toStdString().c_str(), strVal.size());
        if (nb != strVal.size())
            emit sig_erreur("CServeurTcp::onReadyRead ERREUR réponse au client");
        m_soc->write("\x0d\x0a", 2);
    } // else
}

void CServeurTcp::on_erreur(QString mess)
{
    emit sig_erreur(mess);
}
