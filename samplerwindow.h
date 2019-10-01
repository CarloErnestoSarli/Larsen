#ifndef SAMPLERWINDOW_H
#define SAMPLERWINDOW_H

#include <QDialog>
#include "datahandler.h"
#include "geometryprocessor.h"

namespace Ui {
class SamplerWindow;
}

class SamplerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SamplerWindow(QWidget *parent = nullptr);
    ~SamplerWindow();

    void SetSamplingOption(int option);
    int GetSamplingOption();
    void SetDatasetOptions(std::vector<int> options);
    std::vector<int> GetDatasetOptions();

private:
    Ui::SamplerWindow *ui;
//    DataHandler *o_data;
//    GeometryProcessor *o_setUp;

    int m_samplingOption;
    std::vector<int> m_datasetOptions;

    void createSamples(int samplingOption, int datasetOption);

    void createSurfaces(int samplingOption, int datasetOption);
private slots:
    void s_getSamplingOption(int option);
    void s_getIceThicknessToggle(bool toggle);
    void s_getBedToggle(bool toggle);
    void s_getSurfaceToggle(bool toggle);
    void s_getIceMaskToggle(bool toggle);
    void on_samplerButton_clicked();
};

#endif // SAMPLERWINDOW_H
