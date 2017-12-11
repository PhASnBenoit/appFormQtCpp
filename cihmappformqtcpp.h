#ifndef CIHMAPPFORMQTCPP_H
#define CIHMAPPFORMQTCPP_H

#include <QMainWindow>
#include <QTimer>
#include "cbdd.h"
#include "cled.h"
#include "cboutonpoussoir.h"
#include "cperiphrs232.h"
#include "ccapteur_i2c_sht20.h"
#include "ccapteur_spi_tc72.h"
#include "csharedmemory.h"
#include "caff_i2c_grovelcdrgb.h"
#include "cclienttcp.h"
#include "cserveurtcp.h"
#include "global.h"

namespace Ui {
class CIhmAppFormQtCpp;
}

class CIhmAppFormQtCpp : public QMainWindow
{
    Q_OBJECT

public:
    explicit CIhmAppFormQtCpp(QWidget *parent = 0);
    ~CIhmAppFormQtCpp();

private slots:
    void on_pbStartStop_clicked();
    void on_pbOnOffLed_clicked();
    void on_pbLcd_clicked();
    void on_Erreur(QString mess);
    void on_etatBouton(bool etat);
    void on_timerMes();
    void on_timerSgbd();
    void on_timerServeur();
    void on_timerLcd();
    void onFinished();
    void on_recevoirDataDuPeriph(QString data);

    void on_pbEnvoyer_clicked();

signals :
    void sigErreur(QString mess);

private:
    Ui::CIhmAppFormQtCpp *ui;
    CBdd *m_bdd;  // objet statique vers base de données
    CSharedMemory *m_shm;   // pointeur vers objet mémoire partagée
    CLed *m_led;  // pointeur vers objet LED
    CBoutonPoussoir *m_thBt; // pointeur vers objet bouton poussoir
    CAff_i2c_GroveLcdRgb *m_aff;  // pointeur vers objet écran I2C LCD
    CPeriphRs232 *m_periph;  // pointeur vers objet écran RS232C
    CCapteur_I2c_SHT20 *m_thI2c;  // pointeur vers thread objet I2C SHT20
    CCapteur_Spi_TC72 *m_thSpi;  // pointeur vers thread objet SPI TC72
    CClientTcp *m_clientTcp;   // pointeur vers objet client TCP
    CServeurTcp *m_serveurTcp;  // pointeur vers objet serveur TCP
    QTimer *m_interServeur; // pointeur vers objet timer envoi au serveur TCP
    QTimer *m_interSgbd;  // pointeur timer envoi vers SGBD
    QTimer *m_interMes;  // pointeur timer affichage mesures IHM
    QTimer *m_interLcd;  // pointeur timer envoi vers ecran LCD
    bool m_affLibre;   // état pour gestion écran LCD
    bool m_seuil;  // etat alarme ou non pour couleur écran
    bool m_etatBdd;  // etat BDD si connecté
    bool m_etatServeur;  // etat si connecté au serveur
    QThread *thAff;  // pointeur objet thread affichage bienvenue ecran LCD

    void setIhm(bool t);
    void stopAll();
};

#endif // CIHMAPPFORMQTCPP_H
