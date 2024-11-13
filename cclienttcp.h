#ifndef CCLIENTTCP_H
#define CCLIENTTCP_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>

class CClientTcp : public QObject
{
    Q_OBJECT
public:
    explicit CClientTcp(QObject *parent = 0);
    ~CClientTcp();
    int emettre(QString mess);
    int connecter(QString adr, QString port);
    void deconnecter();

signals:
    void sig_data(QString data);
    void sig_erreur(QString mess);
    void sig_evenement(QString eve);

private slots:
    void on_connected();
    void on_disconnected();
    void on_readyRead();
    void on_socketError(QAbstractSocket::SocketError);

private:
    QTcpSocket *_sock;
};

#endif // CCLIENTTCP_H
