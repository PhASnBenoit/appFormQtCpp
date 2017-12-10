#include "ccapteur_spi_tc72.h"

CCapteur_Spi_TC72::CCapteur_Spi_TC72(QObject *parent, int ce, int noMes) :
    QThread(parent)
{
    m_ce = ce;
    m_etat = CONTINUOUS;  // eco d'énergie
    m_noMes = noMes;   // position dans la shm
    m_fin=false;

    m_shm = new CSharedMemory(this, 0);
    connect(m_shm, SIGNAL(sigErreur(QString)), this, SLOT(onErreur(QString)));
    m_shm->attacherSeulement();

    m_spi = new CSpi(this, m_ce, 5000000, true);
    connect(m_spi, SIGNAL(sigErreur(QString)), this, SLOT(onErreur(QString)));
    reset();  // reset soft du capteur
    setMode(m_etat);  // mode eco par défaut
    qDebug() << "Objet CCapteur_Spi_TC72 créé !";

}

CCapteur_Spi_TC72::~CCapteur_Spi_TC72()
{
    delete m_spi;
    m_shm->detach();
    delete m_shm;
    qDebug() << "Objet CCapteur_Spi_TC72 détruit !";

}

int CCapteur_Spi_TC72::setMode(T_ETAT etat)
{
    quint8 trame[2];
    m_etat = etat;
    trame[0]=REG_CTRL|W;  // mode écriture
    trame[1]=etat;
    int nb=m_spi->ecrireNOctets(trame,2);
    if (nb != 2) {
         emit sigErreur("CCapteur_Spi_TC72::setMode ERREUR écriture");
    } // if nb
    msleep(200);
    return nb;
}

int CCapteur_Spi_TC72::reset()
{
    quint8 trame[2];
    trame[0]=REG_CTRL|W;  // mode écriture
    trame[1]=RESET;
    int nb=m_spi->ecrireNOctets(trame,2);
    if (nb != 2) {
         emit sigErreur("CCapteur_Spi_TC72::reset ERREUR écriture");
    } // if nb
    msleep(10);
    return nb;
}

float CCapteur_Spi_TC72::getTemperature()
{
    quint8 data[4] = {REG_MSB};
    int nb=m_spi->lireEcrire(data,4); // demande lecture
    if (nb != 4) {
         emit sigErreur("CCapteur_Spi_TC72::getTemperature ERREUR écriture");
    } // if nb
    float temp;
    temp = (float)data[1];  // partie entière
    if (data[2]==0x80) temp+=0.50;  // précision 1/2 degré
    if (data[3]==0x40) temp+=0.25;  // précision au 1/4 degré
    return temp;
}

quint8 CCapteur_Spi_TC72::getManufacturer()
{
    quint8 data[2] = {REG_ID};
    int nb=m_spi->lireEcrire(data,2); // demande lecture
    if (nb != 2) {
         emit sigErreur("CCapteur_Spi_TC72::getManufacturer ERREUR écriture");
    } // if nb
//    qDebug() << "id=" << QString::number(data[1],16);
    return data[1];
}

void CCapteur_Spi_TC72::run()
{
    float temp;

    while (!m_fin) {
        temp = getTemperature();
//        qDebug() << QString::number(temp);
        m_shm->ecrire(m_noMes, temp);
        msleep(500); // attente TC72 maj temp
    } // wh
}

quint8 CCapteur_Spi_TC72::getControleRegister()
{
    quint8 adr[2] = {REG_CTRL};
    int nb=m_spi->ecrireNOctets(adr,1); // demande lecture
    if (nb != 1) {
         emit sigErreur("CCapteur_Spi_TC72::getControleRegister ERREUR écriture");
    } // if nb
    //msleep(100);
    quint8 cr;
    m_spi->lireNOctets(&cr, 1);
    if (nb != 1) {
         emit sigErreur("CCapteur_Spi_TC72::getControleRegister ERREUR lecture");
    } // if nb
    return cr;
}

int CCapteur_Spi_TC72::setControleRegister(quint8 val)
{
    quint8 trame[2];
    trame[0]=REG_CTRL;
    trame[1]=val;  // val du CR
    int nb=m_spi->ecrireNOctets(trame,2);
    if (nb != 2) {
         emit sigErreur("CCapteur_Spi_TC72::setControleRegister ERREUR écriture");
    } // if nb
    return nb;
}

void CCapteur_Spi_TC72::onErreur(QString mess)
{
   emit sigErreur(mess);
}
