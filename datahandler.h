/**
 * @file camera3D.h
 * @author Carlo Sarli
 * @date 30 August 2019
 * @brief This class provides Camera functionalty for  the canvas.
 *
 * Detailed description goes here.
 */

#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QFile>
#include <QDebug>
#include <QtMath>
#include <QIODevice>
#include <QDataStream>
#include <QVector3D>

#include "constants.h"
#include "vertex.h"

class DataHandler
{
public:
    /**
     * @brief DataHandler
     */
    DataHandler();

    /**
     * @brief DataHandler overloaded constructor
     * @param option the dataset option
     */
    DataHandler(int option);

    void Sampler(int samplingSFactor);
    void BinFileWithNormals(int res);
    void FileOfPoints();
    std::vector<std::vector<float>> ReadPointsFromBinary(int res);
    float Normalize(float min, float max, float normMin, float normMax, float value);

    std::vector<std::vector<float>> ReadPointsFromCsv(int res);

    void WriteVerticesToBin(int res, std::vector<Vertex> vertice);
    void WriteIndecesToBins(int res, std::vector<int> indeces);

    std::vector<int> ReadIndecesFromBins(int res, int option);
    std::vector<Vertex> ReadVerticesFromBin(int res, int option);
    void AverageSampler(int recursion);

    void SetOption(int option);
    int GetOption();

private:

    int m_option;

    bool checkStringIsDigit(QString toCheck);
    float calculateNormal(Constants::Vector vec);


    int dimensionToFactor(int dimension);
    int factorToDimension(int factor);
    int recursionToDimension(int factor);
};

#endif // DATAHANDLER_H
