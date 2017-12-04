#include "ccapteur_i2c_sht20.h"

CCapteur_I2c_SHT20::CCapteur_I2c_SHT20(QObject *parent) :
    QThread(parent)
{
    m_shm = new CSharedMemory(this);
    connect(m_shm, SIGNAL(sigErreur(QString)), this, SLOT(onErreur(QString)));
    m_shm->attacherSeulement();

    m_i2c = CI2c::getInstance(this, '1');
    connect(m_i2c, SIGNAL(sigErreur(QString)), this, SLOT(onErreur(QString)));
    m_fin=false;
}

CCapteur_I2c_SHT20::~CCapteur_I2c_SHT20()
{
    CI2c::freeInstance();
    m_shm->detach();
    delete m_shm;
    qDebug() << "Objet CCapteur_I2c_SHT20 détruit !";

}

void CCapteur_I2c_SHT20::run()
{
    float mesureHum, mesureTemp;

     while(!m_fin) {
         // écriture de la mesure dans le segment de mémoire partagé
         mesureHum = lireMesureHum();
         usleep(100000);
         mesureTemp = lireMesureTemp();
         m_shm->lock(); // on prend la mémoire partagée
         m_shm->ecrire(1, mesureTemp);  // écriture dans la mémoire partagée
         m_shm->ecrire(2, mesureHum);  // écriture dans la mémoire partagée
         m_shm->unlock(); // on libère la mémmoire partagée
         sleep(1); // lecture toutes les s
     } // while
}

void CCapteur_I2c_SHT20::onErreur(QString mess)
{
    emit sigErreur(mess);
}

float CCapteur_I2c_SHT20::lireMesureHum()
{
    float hum;
    unsigned char lecture[3];
    unsigned char ecriture[1];
    int res;

    ecriture[0] = COM_MES_HUM;
    m_i2c->ecrire(ADR, ecriture, 1);
    usleep(100000);
    res=m_i2c->lire(ADR, lecture, 2);
    if (res != 2) {
        QString mess="CCapteur_I2c_SHT20::lireMesureHum ERREUR Lecture";
        emit sigErreur(mess);
        return -1;
    } // if res
    unsigned char MSB = lecture[0];
    unsigned char LSB = lecture[1]&0x03;
    hum=((MSB<<8)+LSB);
    hum = -6+125*hum/65536;
    return hum;
} // lireMesHum

float CCapteur_I2c_SHT20::lireMesureTemp()
{
    float temp;
    unsigned char lecture[2];
    unsigned char ecriture[1];
    int res;

    ecriture[0] = COM_MES_TEMP;
    m_i2c->ecrire(ADR, ecriture, 1);
    usleep(100000);
    res=m_i2c->lire(ADR, lecture, 2);
    if (res != 2) {
        QString mess="CCapteur_I2c_SHT20::lireMesureTemp ERREUR Lecture";
        emit sigErreur(mess);
        return -1;
     } // if res
    unsigned char MSB = lecture[0];
    unsigned char LSB = lecture[1]&0x03;
    temp = ((MSB<<8)+LSB);
    temp = -46.85+175.72*temp/65536;
    return temp;
} // lire MesTemp
