#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

#include "connector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    //format.setDepthBufferSize(24);

    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat:: CoreProfile);
    format.setVersion(4,5);

    QSurfaceFormat::setDefaultFormat(format);



    MainWindow w;
    w.show();

//    Connector *connector = new Connector();

    return a.exec();
}



