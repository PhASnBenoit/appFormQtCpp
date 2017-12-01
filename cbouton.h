#ifndef CBOUTON_H
#define CBOUTON_H

#include <QThread>
#include "/home/pi/devQt/biblis/cgpio.h"

class CBouton : public QThread
{
    Q_OBJECT
public:
    explicit CBouton(QObject *parent = 0, int noGpio = 22);
    ~CBouton();

private:
    CGpio *gpio;
    void run();
    int mValMem;  // état mémoire

signals:
    void sigEtatBouton(bool etat);
    void sigErreur(QString mess);

private slots:
    void onErreur(QString mess);

};

#endif // CBOUTON_H
