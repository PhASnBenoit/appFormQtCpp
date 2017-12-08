#ifndef CCAPTEUR_I2C_SHT20_H
#define CCAPTEUR_I2C_SHT20_H

#include <QThread>
#include "global.h"
#include "csharedmemory.h"
#include "/home/pi/devQt/biblis/ci2c.h"

#define ADR 0x40 // 0x40 + bit LSB à 0 pour write
#define COM_MES_TEMP 0xf3
#define COM_MES_HUM 0xf5
#define COM_RESET 0xfe
#define COM_READ_REG 0xe7
#define COM_WRITE_REG 0xe6

class CCapteur_I2c_SHT20 : public QThread
{
    Q_OBJECT

public:
    explicit CCapteur_I2c_SHT20(QObject *parent = 0, int noMesBase = 1);
    ~CCapteur_I2c_SHT20();
    bool m_fin;

private:
    CSharedMemory *m_shm;
    CI2c *m_i2c;
    int m_noMesBase;
    void run();  // méthode virtuelle à implémenter, contenu du thread
    float lireMesureHum();
    float lireMesureTemp();
signals:
    void sigErreur(QString mess);

private slots:
    void onErreur(QString mess);

};

#endif // CCAPTEURTEMPHUMI2C_H
