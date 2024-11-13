#include "ccapteur_i2c_sht20.h"

CCapteur_I2c_SHT20::CCapteur_I2c_SHT20(QObject *parent, int noMesBase)
{
    _shm = new CSharedMemory(this, sizeof(T_SHM_DATA));
    connect(_shm, SIGNAL(sig_erreur(QString)), this, SLOT(on_erreur(QString)));
    _shm->attacherSeulement();

    _i2c = CI2c::getInstance(this, '1');
    connect(_i2c, SIGNAL(sig_erreur(QString)), this, SLOT(on_erreur(QString)));
    _fin=false;
    m_noMesBase = noMesBase;
    qDebug() << "Objet CCapteur_I2c_SHT20 créé !";
}

CCapteur_I2c_SHT20::~CCapteur_I2c_SHT20()
{
    CI2c::freeInstance();
    _shm->detach();
    delete _shm;
    qDebug() << "Objet CCapteur_I2c_SHT20 détruit !";

}

void CCapteur_I2c_SHT20::on_go()
{
    float mesureHum, mesureTemp;

     while(!_fin) {
         // écriture de la mesure dans le segment de mémoire partagé
         mesureHum = lireMesureHum();
         usleep(100000);
         mesureTemp = lireMesureTemp();
         _shm->lock(); // on prend la mémoire partagée
             _shm->ecrire(m_noMesBase, mesureTemp);  // écriture dans la mémoire partagée
             _shm->ecrire(m_noMesBase+1, mesureHum);  // écriture dans la mémoire partagée
         _shm->unlock(); // on libère la mémmoire partagée
         sleep(1); // lecture toutes les s
     } // while
}

void CCapteur_I2c_SHT20::on_erreur(QString mess)
{
    emit sig_erreur(mess);
}

float CCapteur_I2c_SHT20::lireMesureHum()
{
    float hum;
    unsigned char lecture[3];
    unsigned char ecriture[1];
    int res;

    ecriture[0] = COM_MES_HUM;
    _i2c->ecrire(ADR, ecriture, 1);
    usleep(100000);
    res=_i2c->lire(ADR, lecture, 2);
    if (res != 2) {
        QString mess="CCapteur_I2c_SHT20::lireMesureHum ERREUR Lecture";
        emit sig_erreur(mess);
        return -1;
    } // if res
    unsigned char MSB = lecture[0];
    unsigned char LSB = lecture[1]&0xF0;
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
    _i2c->ecrire(ADR, ecriture, 1);
    usleep(100000);
    res=_i2c->lire(ADR, lecture, 2);
    if (res != 2) {
        QString mess="CCapteur_I2c_SHT20::lireMesureTemp ERREUR Lecture";
        emit sig_erreur(mess);
        return -1;
     } // if res
    unsigned char MSB = lecture[0];
    unsigned char LSB = lecture[1]&0xFC;
    temp = ((MSB<<8)+LSB);
    temp = -46.85+175.72*temp/65536;
    return temp;
} // lire MesTemp
