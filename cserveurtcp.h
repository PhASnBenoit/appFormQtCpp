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
    void sigErreur(QString mess);
    void sigEvenement(QString eve);

private slots:
    void onSocketError(QAbstractSocket::SocketError err);
    void onNewConnection();
    void onReadyRead();
    void onErreur(QString mess);

};

#endif // CSERVEURTCP_H
