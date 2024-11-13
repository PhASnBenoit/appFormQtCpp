#ifndef CLED_H
#define CLED_H

#include <QObject>
#include <QDebug>
#include "qdebug.h"

#include "/home/pi/devQt/biblis/cgpio2024.h"


class CLed : public QObject
{
    Q_OBJECT

public:
    explicit CLed(QObject *parent = 0, int noGpio = 27);
    ~CLed();
    int switchOn();
    int switchOff();

private:
    CGpio2024 *_gpio27;

signals:
    void sig_erreur(QString mess);

private slots:
    void on_erreur(QString mess);
};

#endif // CLED_H
