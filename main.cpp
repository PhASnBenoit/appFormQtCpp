#include "cgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CGui w;
    w.show();

    return a.exec();
}
