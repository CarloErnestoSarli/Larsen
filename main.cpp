#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

#include "datahandler.h"

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

//    DataHandler *d = new DataHandler();
//    d->Sampler(2);
//    d->Sampler(4);
//    d->Sampler(8);
//    d->Sampler(16);
//    d->Sampler(32);
//    d->Sampler(64);
//    d->Sampler(128);
//    d->Sampler(256);
//    d->BinFileWithNormals(52);
//    d->BinFileWithNormals(103);
//    d->BinFileWithNormals(203);
//    d->BinFileWithNormals(393);
//    d->BinFileWithNormals(741);
//    d->BinFileWithNormals(1334);
//    d->BinFileWithNormals(2223);
//    d->BinFileWithNormals(3334);
//    d->BinFileWithNormals(6667);
//    d->FileOfPoints();

    return a.exec();
}


//{
//case 256:
//    dimension = 52;
//    break;
//case 128:
//    dimension = 103;
//    break;
//case 64:
//    dimension = 203;
//    break;
//case 32:
//    dimension = 393;
//    break;
//case 16:
//    dimension = 741;
//    break;
//case 8:
//    dimension = 1334;
//    break;
//case 4:
//    dimension = 2223;
//    break;
//case 2:
//    dimension = 3334;
//    break;
//case 1:
//    dimension = 6667;
//    break;
//}
