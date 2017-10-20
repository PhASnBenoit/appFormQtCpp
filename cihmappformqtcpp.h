#ifndef CIHMAPPFORMQTCPP_H
#define CIHMAPPFORMQTCPP_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTimer>
#include <QSharedMemory>
#include "cled.h"
#include "cbouton.h"
#include "cperiphrs232.h"
#include "ccapteurtemphumi2c.h"
#include "ccapteurtempspi.h"
#include "csharedmemory.h"
#include "global.h"

#define GPIO22 22
#define GPIO27 27

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
    void erreur(QString mess);

private:
    Ui::CIhmAppFormQtCpp *ui;
    QSqlDatabase bdd;
    CSharedMemory *mShm;
    CLed *led;
    CBouton *thread_bt;
    CPeriphRs232 *periph;
    CCapteurTempHumI2c *thI2c;
    CCapteurTempSpi *tSpi;
    QTimer *interServeur;
    QTimer *interSgbd;

    void setIhm(bool t);
};

#endif // CIHMAPPFORMQTCPP_H
