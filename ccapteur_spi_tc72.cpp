#include "ccapteur_spi_tc72.h"

CCapteur_Spi_TC72::CCapteur_Spi_TC72(QObject *parent, int ce, int noMes)
{
    _ce = ce;
    _etat = CONTINUOUS;  // eco d'énergie
    _noMes = noMes;   // position dans la shm
    _fin=false;

    m_shm = new CSharedMemory(this, sizeof(T_SHM_DATA));
    connect(m_shm, SIGNAL(sig_erreur(QString)), this, SLOT(on_erreur(QString)));
    m_shm->attacherSeulement();

    _spi = new CSpi(this, _ce, 5000000, true, SPI_MODE_1);
    connect(_spi, SIGNAL(sig_erreur(QString)), this, SLOT(on_erreur(QString)));
    reset();  // reset soft du capteur
    setMode(_etat);  // mode eco par défaut
    qDebug() << "Objet CCapteur_Spi_TC72 créé !";

}

CCapteur_Spi_TC72::~CCapteur_Spi_TC72()
{
    delete _spi;
    m_shm->detach();
    delete m_shm;
    qDebug() << "Objet CCapteur_Spi_TC72 détruit !";

}

int CCapteur_Spi_TC72::setMode(T_ETAT etat)
{
    quint8 trame[2];
    _etat = etat;
    trame[0]=REG_CTRL|W;  // mode écriture
    trame[1]=etat;
    int nb=_spi->ecrireNOctets(trame,2);
    if (nb != 2) {
         emit sig_erreur("CCapteur_Spi_TC72::setMode ERREUR écriture");
    } // if nb
    QThread::msleep(200);
    return nb;
}

int CCapteur_Spi_TC72::reset()
{
    quint8 trame[2];
    trame[0]=REG_CTRL|W;  // mode écriture
    trame[1]=RESET;
    int nb=_spi->ecrireNOctets(trame,2);
    if (nb != 2) {
         emit sig_erreur("CCapteur_Spi_TC72::reset ERREUR écriture");
    } // if nb
    QThread::msleep(10);
    return nb;
}

float CCapteur_Spi_TC72::getTemperature()
{
    quint8 data[4] = {REG_MSB};
    int nb=_spi->lireEcrire(data,4); // demande lecture
    if (nb != 4) {
         emit sig_erreur("CCapteur_Spi_TC72::getTemperature ERREUR écriture");
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
    int nb=_spi->lireEcrire(data,2); // demande lecture
    if (nb != 2) {
         emit sig_erreur("CCapteur_Spi_TC72::getManufacturer ERREUR écriture");
    } // if nb
//    qDebug() << "id=" << QString::number(data[1],16);
    return data[1];
}

void CCapteur_Spi_TC72::on_go()
{
    float temp;

    while (!_fin) {
        temp = getTemperature();
//        qDebug() << QString::number(temp);
        m_shm->ecrire(_noMes, temp);
        QThread::msleep(500); // attente TC72 maj temp
    } // wh
}

quint8 CCapteur_Spi_TC72::getControleRegister()
{
    quint8 adr[2] = {REG_CTRL};
    int nb=_spi->ecrireNOctets(adr,1); // demande lecture
    if (nb != 1) {
         emit sig_erreur("CCapteur_Spi_TC72::getControleRegister ERREUR écriture");
    } // if nb
    //msleep(100);
    quint8 cr;
    _spi->lireNOctets(&cr, 1);
    if (nb != 1) {
         emit sig_erreur("CCapteur_Spi_TC72::getControleRegister ERREUR lecture");
    } // if nb
    return cr;
}

int CCapteur_Spi_TC72::setControleRegister(quint8 val)
{
    quint8 trame[2];
    trame[0]=REG_CTRL;
    trame[1]=val;  // val du CR
    int nb=_spi->ecrireNOctets(trame,2);
    if (nb != 2) {
         emit sig_erreur("CCapteur_Spi_TC72::setControleRegister ERREUR écriture");
    } // if nb
    return nb;
}

void CCapteur_Spi_TC72::on_erreur(QString mess)
{
   emit sig_erreur(mess);
}
