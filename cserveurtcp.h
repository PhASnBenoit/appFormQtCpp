#ifndef CSERVEURTCP_H
#define CSERVEURTCP_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include "global.h"
#include "csharedmemory.h"

class CServeurTcp : public QObject
{
    Q_OBJECT

public:
    explicit CServeurTcp(QObject *parent = 0);
    ~CServeurTcp();

private:
    QObject *m_parent;
    QTcpServer *m_serv;
    QTcpSocket *m_soc;
    CSharedMemory *m_shm;

signals:
    void sig_erreur(QString mess);
    void sig_evenement(QString eve);

private slots:
    void on_socketError(QAbstractSocket::SocketError err);
    void on_newConnection();
    void on_readyRead();
    void on_erreur(QString mess);
};

#endif // CSERVEURTCP_H
