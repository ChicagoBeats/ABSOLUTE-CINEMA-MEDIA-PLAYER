#include <QApplication>
#include "app/MainWindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setOrganizationName("X-MEDIA");
    app.setApplicationName("AbsoluteCinema");
    MainWindow w;
    w.resize(1280, 720);
    w.show();
    return app.exec();
}
