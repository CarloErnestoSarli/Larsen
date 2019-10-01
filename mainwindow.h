/**
 * @file camera3D.h
 * @author Carlo Sarli
 * @date 30 August 2019
 * @brief This class provides Camera functionalty for  the canvas.
 *
 * Detailed description goes here.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "samplerwindow.h"
#include "colourmapdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    SamplerWindow *samplerWindow;
    ColourMapDialog *colourMapDialog;

public slots:
    void S_openSamplerWindow();
    void S_openColourMapDialog();
    void S_GetIceThicknessMap(int map);
    void S_GetBedMap(int map);

signals:
    void Si_SetIceThicknessMapSelection(int map);
    void Si_SetBedMapSelection(int map);


};

#endif // MAINWINDOW_H
