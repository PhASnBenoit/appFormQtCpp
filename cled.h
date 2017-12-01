#ifndef CLED_H
#define CLED_H

#include <QObject>
#include "/home/pi/devQt/biblis/cgpio.h"


class CLed : public QObject
{
    Q_OBJECT

public:
    explicit CLed(QObject *parent = 0, int noGpio = 4);
    ~CLed();
    int switchOn();
    int switchOff();

private:
    CGpio *gpio;

signals:
    void sigErreur(QString mess);

private slots:
    void onErreur(QString mess);
};

#endif // CLED_H
