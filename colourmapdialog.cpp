#include "colourmapdialog.h"
#include "ui_colourmapdialog.h"

ColourMapDialog::ColourMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColourMapDialog)
{
    ui->setupUi(this);
}

ColourMapDialog::~ColourMapDialog()
{
    delete ui;
}

void ColourMapDialog::S_GetIceThicknessMapSelection0()
{
    emit Si_SetIceThicknessMapSelection(0);
}

void ColourMapDialog::S_GetIceThicknessMapSelection1()
{
    emit Si_SetIceThicknessMapSelection(1);
}

void ColourMapDialog::S_GetIceThicknessMapSelection2()
{
    emit Si_SetIceThicknessMapSelection(2);
}

void ColourMapDialog::S_GetBedMapSelection0()
{
    emit Si_SetBedMapSelection(0);
}

void ColourMapDialog::S_GetBedMapSelection1()
{
    emit Si_SetBedMapSelection(1);
}

void ColourMapDialog::S_GetBedMapSelection2()
{
    emit Si_SetBedMapSelection(2);
}




