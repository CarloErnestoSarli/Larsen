#ifndef COLOURMAPDIALOG_H
#define COLOURMAPDIALOG_H

#include <QDialog>
#include "canvas.h"
#include "colourmapdialog.h"

namespace Ui {
class ColourMapDialog;
}

class ColourMapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColourMapDialog(QWidget *parent = nullptr);
    ~ColourMapDialog();

private:
    Ui::ColourMapDialog *ui;

public slots:
    void S_GetIceThicknessMapSelection0();
    void S_GetIceThicknessMapSelection1();
    void S_GetIceThicknessMapSelection2();
    void S_GetBedMapSelection0();
    void S_GetBedMapSelection1();
    void S_GetBedMapSelection2();

signals:
    void Si_SetIceThicknessMapSelection(int map);
    void Si_SetBedMapSelection(int map);
};

#endif // COLOURMAPDIALOG_H
