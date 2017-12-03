#include "ccapteur_spi_tc72.h"

CCapteur_Spi_TC72::CCapteur_Spi_TC72(QObject *parent, int ce, int noMes) :
    QThread(parent)
{
    m_ce = ce;
    m_etat = ONESHOT;  // eco d'énergie
    m_noMes = noMes;   // position dans la shm

    m_shm = new CSharedMemory(this, 0);
    connect(m_shm, SIGNAL(sigErreur(QString)), this, SLOT(onErreur(QString)));
    m_shm->attacherSeulement();

    m_spi = new CSpi(this, '0', 7000000);
    connect(m_spi, SIGNAL(sigErreur(QString)), this, SLOT(onErreur(QString)));
    setMode(m_etat);  // mode eco par défaut
}

CCapteur_Spi_TC72::~CCapteur_Spi_TC72()
{
    delete m_spi;
    m_shm->detach();
    delete m_shm;
}

int CCapteur_Spi_TC72::setMode(T_ETAT etat)
{
    quint8 trame[2];
    trame[0]=etat;
    trame[1]=REG_CTRL|W;  // mode écriture
    int nb=m_spi->ecrireNOctets(trame,2);
    return nb;
}

float CCapteur_Spi_TC72::getTemperature()
{
    quint8 adr = REG_MSB;
    m_spi->ecrireNOctets(&adr,1); // demande lecture
    msleep(100);
    char data[3];
    float temp;
    m_spi->lireNOctets(data, 3); // MSB + LSB + CR
    temp = float(data[0]);  // partie entière
    if (data[1]==0x80) temp+=0.50;  // précision 1/2 degré
    if (data[1]==0x40) temp+=0.25;  // précision au 1/4 degré
    return temp;
}

quint8 CCapteur_Spi_TC72::getManufacturer()
{
    quint8 adr = REG_ID;
    m_spi->ecrireNOctets(&adr,1); // demande lecture
//    msleep(200);
    char id;
    m_spi->lireNOctets(&id,1);
    qDebug() << "id=" << QString::number(id,16);
    return (quint8)id;
}

void CCapteur_Spi_TC72::run()
{
    float temp;
    setMode(CONTINUOUS);
    while (1) {
        temp = getTemperature();
        qDebug() << QString::number(temp);
        m_shm->ecrire(m_noMes, temp);
        msleep(1000); // attente TC72 maj temp
    } // wh
}

quint8 CCapteur_Spi_TC72::getControleRegister()
{
    quint8 adr = REG_CTRL;
    m_spi->ecrireNOctets(&adr,1); // demande lecture
    msleep(100);
    char cr;
    m_spi->lireNOctets(&cr, 1);
    return (quint8)cr;
}

int CCapteur_Spi_TC72::setControleRegister(quint8 val)
{
    quint8 trame[2];
    trame[0]=REG_CTRL;
    trame[1]=val;  // val du CR
    int nb=m_spi->ecrireNOctets(trame,2);
    return nb;
}

void CCapteur_Spi_TC72::onErreur(QString mess)
{
   emit sigErreur(mess);
}
