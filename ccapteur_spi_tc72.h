#ifndef CCAPTEUR_SPI_TC72_H
#define CCAPTEUR_SPI_TC72_H

#include <QThread>
#include "csharedmemory.h"
#include "/home/pi/devQt/biblis/cspi.h"
#include "global.h"

#define ADRESSE 0x80
#define REG_CTRL 0x00
#define REG_LSB 0x01
#define REG_MSB 0x02
#define REG_ID 0x03   // 0x54
#define W 0x80
#define RESET 0xfe

typedef enum {
    CONTINUOUS=0,
    ONESHOT=0x11
} T_ETAT;

class CCapteur_Spi_TC72 : public QThread
{
    Q_OBJECT

public:
    explicit CCapteur_Spi_TC72(QObject *parent = 0, int ce = 0, int noMes = 0);
    ~CCapteur_Spi_TC72();
    bool m_fin;
    quint8 getManufacturer();

private:
    CSharedMemory *m_shm;
    CSpi *m_spi;
    int m_ce;
    int m_noMes;
    T_ETAT m_etat;   // état du capteur

    void run();  // thread méthode redéfinie
    int setMode(T_ETAT etat); // continous ou oneshot
    int reset();
    float getTemperature();
    quint8 getControleRegister();
    int setControleRegister(quint8 val);

signals:
    void sigErreur(QString mess);

private slots:
    void onErreur(QString mess);

};

#endif // CCAPTEURTEMPSPI_H
