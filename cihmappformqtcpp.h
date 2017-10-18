#ifndef CIHMAPPFORMQTCPP_H
#define CIHMAPPFORMQTCPP_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSharedMemory>
#include <cled.h>
#include <cbouton.h>

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

    void on_pbOnOffLed_clicked();

signals :
    void erreur(QString mess);

private:
    Ui::CIhmAppFormQtCpp *ui;
    QSqlDatabase bdd;
    QSharedMemory *shm;
    CLed *led;
    CBouton *thread_bt;

};

#endif // CIHMAPPFORMQTCPP_H
