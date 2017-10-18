#ifndef CCAPTEURTEMPHUMI2C_H
#define CCAPTEURTEMPHUMI2C_H

#include <QObject>
#include <QThread>

class CCapteurTempHumI2c : public QThread
{
    Q_OBJECT

public:
    explicit CCapteurTempHumI2c(QObject *parent = 0);
};

#endif // CCAPTEURTEMPHUMI2C_H
