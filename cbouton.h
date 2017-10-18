#ifndef CBOUTON_H
#define CBOUTON_H

#include <QThread>
#include "/home/philippe/devQt/biblis/cgpio.h"

class CBouton : public QThread
{
    Q_OBJECT
public:
    explicit CBouton(QObject *parent = 0, int noGpio = 22);
    ~CBouton();

private:
    CGpio *gpio;

signals:

public slots:


};

#endif // CBOUTON_H
