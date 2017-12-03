#ifndef CBOUTONPOUSSOIR_H
#define CBOUTONPOUSSOIR_H

#include <QThread>
#include "/home/pi/devQt/biblis/cgpio.h"

class CBoutonPoussoir : public QThread
{
    Q_OBJECT
public:
    explicit CBoutonPoussoir(QObject *parent = 0, int noGpio = 22);
    ~CBoutonPoussoir();

private:
    CGpio *gpio;
    void run();
    int m_valMem;  // état mémoire

signals:
    void sigEtatBouton(bool etat);
    void sigErreur(QString mess);

private slots:
    void onErreur(QString mess);

};

#endif // CBOUTONPOUSSOIR_H
