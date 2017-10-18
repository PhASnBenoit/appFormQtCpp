#include "cihmappformqtcpp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CIhmAppFormQtCpp w;
    w.show();

    return a.exec();
}
