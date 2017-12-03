#include "ccapteur_i2c_sht20.h"

CCapteur_I2c_SHT20::CCapteur_I2c_SHT20(QObject *parent) :
    QThread(parent)
{
    m_shm = new CSharedMemory(this);
    m_shm->attacherSeulement();
}

CCapteur_I2c_SHT20::~CCapteur_I2c_SHT20()
{
    delete m_shm;
}

void CCapteur_I2c_SHT20::onErreur(QString mess)
{
    emit sigErreur(mess);
}
