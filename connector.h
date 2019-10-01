#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>
#include "canvas.h"
#include "colourmapdialog.h"
#include "mainwindow.h"

class Connector : public QObject
{
    Q_OBJECT

public:
    Connector();
};

#endif // CONNECTOR_H
