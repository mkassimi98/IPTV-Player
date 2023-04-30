#include "../src/gui/iptvplayer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IPTVPlayer w;
    w.show();
    return a.exec();
}
