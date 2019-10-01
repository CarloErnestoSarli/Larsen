#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->c_resAvgCombo->setHidden(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::S_openSamplerWindow()
{
    samplerWindow = new SamplerWindow(this);
    samplerWindow->show();

}

void MainWindow::S_openColourMapDialog()
{
    colourMapDialog = new ColourMapDialog(this);
   connect (colourMapDialog, &ColourMapDialog::Si_SetIceThicknessMapSelection, this, &MainWindow::S_GetIceThicknessMap);
   connect (colourMapDialog, &ColourMapDialog::Si_SetBedMapSelection, this, &MainWindow::S_GetBedMap);

    colourMapDialog->show();

}

void MainWindow::S_GetIceThicknessMap(int map)
{
    connect(this, &MainWindow::Si_SetIceThicknessMapSelection, ui->openGLWidget, &Canvas::S_GetIceThicknessMap);
    emit Si_SetIceThicknessMapSelection(map);
}

void MainWindow::S_GetBedMap(int map)
{
    connect(this, &MainWindow::Si_SetBedMapSelection, ui->openGLWidget, &Canvas::S_GetBedMap);
    emit Si_SetBedMapSelection(map);
}

