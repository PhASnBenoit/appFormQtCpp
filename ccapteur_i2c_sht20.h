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

class CCapteur_I2c_SHT20 : public QObject
{
    Q_OBJECT

public:
    explicit CCapteur_I2c_SHT20(QObject *parent = nullptr, int noMesBase = 1);
    ~CCapteur_I2c_SHT20();
    bool _fin;

private:
    CSharedMemory *_shm;
    CI2c *_i2c;
    int m_noMesBase;
    float lireMesureHum();
    float lireMesureTemp();
signals:
    void sig_erreur(QString mess);

public slots:
    void on_go();  // méthode virtuelle à implémenter, contenu du thread

private slots:
    void on_erreur(QString mess);

};

#endif // CCAPTEURTEMPHUMI2C_H
