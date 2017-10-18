#ifndef CCAPTEURTEMPSPI_H
#define CCAPTEURTEMPSPI_H

#include <QThread>

class CCapteurTempSpi : public QThread
{
    Q_OBJECT
public:
    explicit CCapteurTempSpi(QObject *parent = 0);

signals:

public slots:

};

#endif // CCAPTEURTEMPSPI_H
