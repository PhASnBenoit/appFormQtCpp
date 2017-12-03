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

signals :
    void sigErreur(QString mess);

private:
    Ui::CIhmAppFormQtCpp *ui;
    QSqlDatabase m_bdd;
    CSharedMemory *m_shm;
    CLed *m_led;
    CBoutonPoussoir *m_thBt;
    CPeriphRs232 *m_thPeriph;
    CCapteur_I2c_SHT20 *m_thI2c;
    CCapteur_Spi_TC72 *m_thSpi;
    QTimer *m_interServeur;
    QTimer *m_interSgbd;
    QTimer *m_interMes;
    void setIhm(bool t);
};

#endif // CIHMAPPFORMQTCPP_H
