#ifndef CIHMAPPFORMQTCPP_H
#define CIHMAPPFORMQTCPP_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSharedMemory>

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

signals :
    void erreur(QString mess);

private:
    Ui::CIhmAppFormQtCpp *ui;
    QSqlDatabase bdd;
    QSharedMemory *shm;
};

#endif // CIHMAPPFORMQTCPP_H
