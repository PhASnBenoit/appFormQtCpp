#ifndef CGUI_H
#define CGUI_H

#include <QMainWindow>
#include <QTimer>
#include <QPixmap>

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
class CGui;
}

class CGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit CGui(QWidget *parent = 0);
    ~CGui();

private slots:
    void on_pbStartStop_clicked();
    void on_pbOnOffLed_clicked();
    void on_pbLcd_clicked();
    void on_erreur(QString mess);
    void on_etatBouton(bool etat);
    void on_timerMes();
    void on_timerSgbd();
    void on_timerServeur();
    void on_timerLcd();
    void on_finished();
    void on_recevoirDataDuPeriph(QString data);
    void on_pbEnvoyer_clicked();

signals :
    void sig_erreur(QString mess);
    void sig_goBp();
    void sig_goCapt();

private:
    Ui::CGui *ui;
    CBdd *_bdd;  // objet statique vers base de données
    CSharedMemory *_shm;   // pointeur vers objet mémoire partagée
    CLed *_led;  // pointeur vers objet LED

    QThread *_thBp;
    CBoutonPoussoir *_bp; // pointeur vers objet bouton poussoir

    QThread *_thSht20;
    CCapteur_I2c_SHT20 *_sht20;  // pointeur vers thread objet I2C SHT20

    QThread *_thTc72;
    CCapteur_Spi_TC72 *_tc72;  // pointeur vers thread objet SPI TC72

    CAff_i2c_GroveLcdRgb *_aff;  // pointeur vers objet écran I2C LCD
    CPeriphRs232 *_periph;  // pointeur vers objet écran RS232C
    CClientTcp *_clientTcp;   // pointeur vers objet client TCP
    CServeurTcp *_serveurTcp;  // pointeur vers objet serveur TCP
    QTimer *_interServeur; // pointeur vers objet timer envoi au serveur TCP
    QTimer *_interSgbd;  // pointeur timer envoi vers SGBD
    QTimer *_interMes;  // pointeur timer affichage mesures IHM
    QTimer *_interLcd;  // pointeur timer envoi vers ecran LCD
    bool _affLibre;   // état pour gestion écran LCD
    bool _seuil;  // etat alarme ou non pour couleur écran
    bool _etatBdd;  // etat BDD si connecté
    bool _etatServeur;  // etat si connecté au serveur
    QThread *_thAff;  // pointeur objet thread affichage bienvenue ecran LCD

    void setIhm(bool t);
    void stopAll();
};

#endif // CGUI_H
