#include "samplerwindow.h"
#include "ui_samplerwindow.h"

#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QThread>

SamplerWindow::SamplerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SamplerWindow)
{
    ui->setupUi(this);

    m_samplingOption = 0;
}

SamplerWindow::~SamplerWindow()
{
    delete ui;
}


void SamplerWindow::createSamples(int samplingOption, int datasetOption)
{
    DataHandler *o_data = new DataHandler(datasetOption);

    if(samplingOption == 0)
    {
        int res[9] =  {52,103, 203, 393, 741, 1334, 2223, 3334, 6667};
        int values[9] =  {1,2,4, 8, 16, 32, 64, 128, 256};

        for(auto i : values)
        {
            o_data->Sampler(i);
            qDebug() << "sampled" << i << "of" << datasetOption;
        }

        for(auto i: res)
        {
            o_data->BinFileWithNormals(i);
            qDebug() << "binned" << i << "of" << datasetOption;
        }

    }else
    {
         int res[9] =   {52, 104, 208, 416, 833, 1666, 3333};

        o_data->AverageSampler(0);

        for(auto i: res)
        {
            o_data->BinFileWithNormals(i);
            qDebug() << "binned" << i << "of" << datasetOption;
        }

    }

    createSurfaces(samplingOption, datasetOption);

}

void SamplerWindow::createSurfaces(int samplingOption, int datasetOption)
{
    DataHandler *o_data = new DataHandler(datasetOption);
    GeometryProcessor *o_setUp = new  GeometryProcessor();
    std::vector<int> values;
    if(samplingOption == 0)
    {
         values = {52,103, 203, 393, 741, 1334, 2223, 3334, 6667};
    }else {
         values = {52, 104, 208, 416, 833, 1666, 3333};
    }

    for(auto i : values)
    {
        std::vector<Vertex> triVerteces;
        std::vector<int> triIndeces;

        o_setUp->CreateTriangles(i, datasetOption);

        QList<QVector3D> list = o_setUp->GetVertList();
        for(auto l : list)
        {
            triVerteces.push_back(Vertex(l/*, *col*/));
        }

        triIndeces = o_setUp->GetTriIndeces();

        o_data->WriteIndecesToBins(i,triIndeces);
        o_data->WriteVerticesToBin(i, triVerteces);

        qDebug() << "created surfaces" << i << "of" << datasetOption;
    }
}




///////////////SLOTS///////////////////
void SamplerWindow::s_getIceThicknessToggle(bool toggle)
{
    if(toggle)
        m_datasetOptions.push_back(0);
}
void SamplerWindow::s_getBedToggle(bool toggle)
{
    if(toggle)
        m_datasetOptions.push_back(1);
}
void SamplerWindow::s_getSurfaceToggle(bool toggle)
{
    if(toggle)
        m_datasetOptions.push_back(2);
}
void SamplerWindow::s_getIceMaskToggle(bool toggle)
{
    if(toggle)
        m_datasetOptions.push_back(3);
}
void SamplerWindow::s_getSamplingOption(int option)
{
    SetSamplingOption(option);
}


void SamplerWindow::on_samplerButton_clicked()
{
    QFuture<void>future1;
    QFuture<void>future2;
    QFuture<void>future3;
    QFuture<void>future4;

    if((std::find(m_datasetOptions.begin(), m_datasetOptions.end(), 0) != m_datasetOptions.end()))
        future1 = QtConcurrent::run(this, &SamplerWindow::createSamples, m_samplingOption, m_datasetOptions.at(std::distance(m_datasetOptions.begin(), std::find(m_datasetOptions.begin(), m_datasetOptions.end(), 0))));
   if((std::find(m_datasetOptions.begin(), m_datasetOptions.end(), 1) != m_datasetOptions.end()))
        future2 = QtConcurrent::run(this, &SamplerWindow::createSamples, m_samplingOption, m_datasetOptions.at(std::distance(m_datasetOptions.begin(), std::find(m_datasetOptions.begin(), m_datasetOptions.end(), 1))));
    if((std::find(m_datasetOptions.begin(), m_datasetOptions.end(), 2) != m_datasetOptions.end()))
        future3 = QtConcurrent::run(this, &SamplerWindow::createSamples, m_samplingOption, m_datasetOptions.at(std::distance(m_datasetOptions.begin(), std::find(m_datasetOptions.begin(), m_datasetOptions.end(), 2))));
    if((std::find(m_datasetOptions.begin(), m_datasetOptions.end(), 3) != m_datasetOptions.end()))
        future4 = QtConcurrent::run(this, &SamplerWindow::createSamples, m_samplingOption, m_datasetOptions.at(std::distance(m_datasetOptions.begin(), std::find(m_datasetOptions.begin(), m_datasetOptions.end(), 3))));


//    for(auto i : m_datasetOptions)
//    {
//        switch(i)
//        {
//        case 0:
//            future1 = QtConcurrent::run(this, &SamplerWindow::createSamples, m_samplingOption, i );
//            break;
//        case 1:
//            future2 = QtConcurrent::run(this, &SamplerWindow::createSamples, m_samplingOption, i );
//            break;
//        case 2:
//            future3 = QtConcurrent::run(this, &SamplerWindow::createSamples, m_samplingOption, i );
//            break;
//        case 3:
//            future4 = QtConcurrent::run(this, &SamplerWindow::createSamples, m_samplingOption, i );
//            break;
//        }

//    }

    future1.waitForFinished();
    future2.waitForFinished();
    future3.waitForFinished();
    future4.waitForFinished();

    this->close();
}


///////////////ACCESSORS///////////////////
void SamplerWindow::SetSamplingOption(int option)
{
    m_samplingOption = option;
}

int SamplerWindow::GetSamplingOption()
{
    return  m_samplingOption;
}

void SamplerWindow::SetDatasetOptions(std::vector<int> option)
{
    m_datasetOptions = option;
}

std::vector<int> SamplerWindow::GetDatasetOptions()
{
    return m_datasetOptions;
}



