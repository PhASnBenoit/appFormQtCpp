#include "cperiphrs232.h"

CPeriphRs232::CPeriphRs232(QObject *parent, QString port, int inter) :
    QThread(parent)
{
}
