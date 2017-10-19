#ifndef CPERIPHRS232_H
#define CPERIPHRS232_H

#include <QThread>

class CPeriphRs232 : public QThread
{
    Q_OBJECT
public:
    explicit CPeriphRs232(QObject *parent = 0);

signals:

public slots:

};

#endif // CPERIPHRS232_H
