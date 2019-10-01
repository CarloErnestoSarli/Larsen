#include "connector.h"

Connector::Connector()
{
    Canvas c;
    MainWindow w;
    ColourMapDialog cmd;

    bool success = connect (&cmd, &ColourMapDialog::Si_SetIceThicknessMapSelection, &w, &MainWindow::S_GetIceThicknessMap);

    qDebug() <<success;
}
