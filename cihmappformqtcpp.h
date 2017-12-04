#ifndef CIHMAPPFORMQTCPP_H
#define CIHMAPPFORMQTCPP_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTimer>
#include <QSharedMemory>
#include "cled.h"
#include "cboutonpoussoir.h"
#include "cperiphrs232.h"
#include "ccapteur_i2c_sht20.h"
#include "ccapteur_spi_tc72.h"
#include "csharedmemory.h"
#include "caff_i2c_grovelcdrgb.h"
//#include "cspiioctl.h"
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
    void on_Erreur(QString mess);
    void on_etatBouton(bool etat);
    void on_pbOnOffLed_clicked();
    void on_timerMes();
    void on_timerSgbd();
    void on_timerServeur();
    void on_timerPeriph();
    void on_timerLcd();
    void on_pbId_clicked();
    void on_pbLcd_clicked();
    void affLibre();

signals :
    void sigErreur(QString mess);

private:
    Ui::CIhmAppFormQtCpp *ui;
    QSqlDatabase m_bdd;
    CSharedMemory *m_shm;
    CLed *m_led;
    CBoutonPoussoir *m_thBt;
//    CSpiIoctl *m_tc72;
    CAff_i2c_GroveLcdRgb *m_aff;
    CPeriphRs232 *m_thPeriph;
    CCapteur_I2c_SHT20 *m_thI2c;
    CCapteur_Spi_TC72 *m_thSpi;
    QTimer *m_interServeur;
    QTimer *m_interSgbd;
    QTimer *m_interMes;
    QTimer *m_interPeriph;
    QTimer *m_interLcd;
    bool m_affLibre;
    QThread *thAff;
    void setIhm(bool t);
};

#endif // CIHMAPPFORMQTCPP_H
