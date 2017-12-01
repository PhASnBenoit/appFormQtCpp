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
#include "ccapteuri2csht20.h"
#include "ccapteurspitc72.h"
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
    QSqlDatabase bdd;
    CSharedMemory *mShm;
    CLed *led;
    CBouton *thBt;
    CPeriphRs232 *thPeriph;
    CCapteurI2cSht20 *thI2c;
    CCapteurSpiTc72 *thSpi;
    QTimer *interServeur;
    QTimer *interSgbd;
    void setIhm(bool t);
};

#endif // CIHMAPPFORMQTCPP_H
