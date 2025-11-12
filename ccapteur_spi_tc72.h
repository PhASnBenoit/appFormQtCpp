#ifndef CCAPTEUR_SPI_TC72_H
#define CCAPTEUR_SPI_TC72_H

#include <QThread>
#include "csharedmemory.h"
#include "../biblis/cspi.h"
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

class CCapteur_Spi_TC72 : public QObject
{
    Q_OBJECT

public:
    explicit CCapteur_Spi_TC72(QObject *parent = nullptr, int ce = 0, int noMes = 0);
    ~CCapteur_Spi_TC72();
    bool _fin;
    quint8 getManufacturer();

private:
    CSharedMemory *m_shm;
    CSpi *_spi;
    int _ce;
    int _noMes;
    T_ETAT _etat;   // état du capteur

    int setMode(T_ETAT etat); // continous ou oneshot
    int reset();
    float getTemperature();
    quint8 getControleRegister();
    int setControleRegister(quint8 val);

signals:
    void sig_erreur(QString mess);

public slots:
    void on_go();  // thread méthode redéfinie

private slots:
    void on_erreur(QString mess);

};

#endif // CCAPTEURTEMPSPI_H
