#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

#include "datahandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat:: CoreProfile);
    format.setVersion(4,5);

    QSurfaceFormat::setDefaultFormat(format);

    MainWindow w;
    w.show();

    DataHandler *d = new DataHandler();
//    d->Sampler(2);
//    d->Sampler(4);
//    d->Sampler(8);
//    d->Sampler(16);
//    d->Sampler(32);
//    d->Sampler(64);
//    d->Sampler(128);
//    d->Sampler(256);
//    d->BinFileWithNormals();
//    d->FileOfPoints();

    return a.exec();
}
