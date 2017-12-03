#ifndef CCAPTEUR_I2C_SHT20_H
#define CCAPTEUR_I2C_SHT20_H

#include <QThread>
#include "global.h"
#include "csharedmemory.h"

class CCapteur_I2c_SHT20 : public QThread
{
    Q_OBJECT

public:
    explicit CCapteur_I2c_SHT20(QObject *parent = 0);
    ~CCapteur_I2c_SHT20();

private:
    CSharedMemory *m_shm;


signals:
    void sigErreur(QString mess);

private slots:
    void onErreur(QString mess);

};

#endif // CCAPTEURTEMPHUMI2C_H
