#include "datahandler.h"
#include "constants.h"

#include <string>
#include <fstream>
#include <QElapsedTimer>

DataHandler::DataHandler()
{

}

void DataHandler::Sampler(int samplingFactor)
{
//    QString inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_thickness.txt";

//    QString inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_bed.txt";

    QString inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_surface.txt";

//    QString inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_thickness.txt";

//    QString outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(factorToDimension(samplingFactor)) + ".csv";

//    QString outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(factorToDimension(samplingFactor)) + "bed.csv";

    QString outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(factorToDimension(samplingFactor)) + "surface.csv";

//    QString outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(factorToDimension(samplingFactor)) + ".csv";

    QFile input(inputPath);
    QFile output(outputPath);

    if(!input.open(QFile::ReadOnly | QFile::Text) | !output.open(QFile::WriteOnly | QFile::Truncate))
    {
        qDebug() << "File(s) do(es) not exist(s)";
    }else
    {
        QTextStream in(&input);
        QTextStream out(&output);

        //skip header
        for(int i = 0; i < 6; i++)
        {
            in.readLine();
        }

        int rowCounter = 0;
        //int columnCounter = 0;
        int everyOther = samplingFactor/2;

        while(!in.atEnd())
        {
            QString line;

            if(rowCounter == 0)
            {
                line = in.readLine();
            }
            else
            {
                for(int y = 0; y < everyOther; y++)
                {
                    in.readLine();
                }
                line = in.readLine();
            }

            QStringList inColumns = line.split(" ");
            QStringList outColumns;

            int columnsNumber = inColumns.size();

            for (int x = 0; x < columnsNumber-everyOther; x++)
            {
                if (x == 0)
                {
                    QString value = inColumns.at(x);
                    if(checkStringIsDigit(value))
                    {
                        outColumns.append(value);
                    }

                }else
                {
                    x += everyOther;
                    QString value = inColumns.at(x);
                    if(checkStringIsDigit(value))
                    {
                        outColumns.append(value);
                    }
                }
            }

            for(auto it : outColumns)
            {
                if(it == "-9999")
                {
                    out << "-1" << ",";
                }else
                {
                    out << it << ",";
                }
            }
            out << "\n";

            rowCounter += everyOther;

        }

        input.close();
        output.close();

    }
}


void DataHandler::BinFileWithNormals(int res)
{
    float normMin = 0;
    float normMax = res;
    float min = -1;
    float max = 46.21;

//    QString inputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(res) + ".csv";

//    QString inputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(res) + "bed.csv";

    QString inputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(res) + "surface.csv";

//    std::string outputPath ="/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + ".raw";

//    std::string outputPath ="/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "bed.raw";

    std::string outputPath ="/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "surface.raw";

    QFile input(inputPath);
    //QFile output(outputPath);
    std::ofstream output(outputPath.c_str(), std::ios::binary);

    //std::vector<float> valuesList;

    //| !output.open(QIODevice::WriteOnly | QIODevice::Truncate
    if(!input.open(QFile::ReadOnly | QFile::Text) | !output.is_open())
    {
        qDebug() << "File(s) do(es) not exist(s)";
        Sampler(dimensionToFactor(res));
        BinFileWithNormals(res);
    }else
    {
        QTextStream in(&input);
        //QDataStream out(&output);


        for (int iy = 0; iy < normMax; iy++) {

            QString line = in.readLine();
            QStringList inColumns = line.split(",");

            for (int ix = 0; ix < normMax; ix++) {

                float z = inColumns.at(ix).toFloat();
                if (z != -1)
                {
                    z = z/1000;
                }
                //float normalZ = Normalize(min, max, normMin, normMax, z);
                //valuesList.push_back(normalZ);
                output.write((char*)&z, sizeof (float));
            }
        }
        input.close();
        output.close();
        qDebug() << "Done";
    }
}



std::vector<std::vector<float>> DataHandler::ReadPointsFromBinary(int res)
{
    QElapsedTimer timer;
    timer.start();

    float size = res;

    std::vector<std::vector<float>> points(res);

//    std::string inputPath = "/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + ".raw";

    std::string inputPath = "/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "bed.raw";

//    std::string inputPath = "/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "surface.raw";


    std::ifstream input(inputPath.c_str(), std::ios::binary);

    if(!input.is_open())
    {
        BinFileWithNormals(res);
        ReadPointsFromBinary(res);
    }else
    {
        float f;

        for (unsigned int y = 0; y < size; y++) {
            for (unsigned int x = 0; x < size; x++) {

                input.read(reinterpret_cast<char*>(&f), sizeof(float));
                points.at(y).push_back( f);
            }
        }
        input.close();
    }
    qDebug() << "The readPointsFromBinary func took" << timer.elapsed() << "milliseconds";

    return points;
}


void DataHandler::WriteVerticesToBin(int res, std::vector<Vertex> vertices )
{
//    std::string outputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + ".bin";

    std::string outputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "bed.bin";

//    std::string outputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "surface.bin";

    std::ofstream output(outputPath.c_str(), std::ios::binary);

    if(!output.is_open())
    {
        qDebug() << "File(s) do(es) not exist(s)";

    }else
    {

        for(auto v : vertices)
        {
            output.write((char*)&v, sizeof (Vertex));
        }
    }
    output.close();
}

void DataHandler::WriteIndecesToBins(int res, std::vector<int>indeces)
{
//    std::string outputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + ".bin";

    std::string outputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "bed.bin";

//    std::string outputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "surface.bin";

    std::ofstream output(outputPath.c_str(), std::ios::binary);

    if(!output.is_open())
    {
        qDebug() << "File(s) do(es) not exist(s)";

    }else
    {

        for(auto i : indeces)
        {
            output.write((char*)&i, sizeof (int));
        }
    }
    output.close();
}

std::vector<Vertex> DataHandler::ReadVerticesFromBin(int res, int option)
{
    std::vector<Vertex> vertices;
    std::string inputPath;

    switch (option) {
    case 0:
       inputPath  = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + ".bin";
        break;
    case 1:
       inputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "bed.bin";
        break;
    case 2:
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "surface.bin";
        break;
    }

    std::ifstream input(inputPath.c_str(), std::ios::binary);

    if(!input.is_open())
    {
        qDebug() << "File(s) do(es) not exist(s)";

    }else
    {

        while(!input.eof())
        {
            Vertex v;
            input.read((char*)&v, sizeof (Vertex));
            vertices.push_back(v);
        }
    }
    input.close();
    return vertices;
}

std::vector<int> DataHandler::ReadIndecesFromBins(int res, int option)
{
    std::vector<int>indeces;

    std::string inputPath;

    switch (option) {
    case 0:
       inputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + ".bin";
        break;
    case 1:
      inputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "bed.bin";
        break;
    case 2:
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "surface.bin";
        break;
    }

    std::ifstream input(inputPath.c_str(), std::ios::binary);

    if(!input.is_open())
    {
        qDebug() << "File(s) do(es) not exist(s)";

    }else
    {

        while(!input.eof())
        {
            int i;
            input.read((char*)&i, sizeof (int));
            indeces.push_back(i);
        }
    }
    input.close();
    return indeces;
}

float DataHandler::Normalize(float min, float max, float normMin, float normMax, float value)
{
    float normal = (normMax - normMin) * (value - min) / (max - min) + normMin;

    return normal;
}

float DataHandler::calculateNormal(Constants::Vector vec)
{
    float normVal = sqrt(pow(vec.x, Constants::SQUARED) + pow(vec.y, Constants::SQUARED) + pow(vec.z, Constants::SQUARED)) * Constants::OCTET;

    return normVal;
}

bool DataHandler::checkStringIsDigit(QString toCheck)
{
    QRegExp re("-?[0-9]+([.][0-9]+)?");
    if(re.exactMatch(toCheck))
    {
        return true;
    }else
    {
        return false;
    }
}

int DataHandler::dimensionToFactor(int dimension)
{
    int factor;
    switch (dimension)
    {
    case 52:
        factor = 256;
        break;
    case 103:
        factor = 128;
        break;
    case 203:
        factor = 64;
        break;
    case 393:
        factor = 32;
        break;
    case 741:
        factor = 16;
        break;
    case 1334:
        factor = 8;
        break;
    case 2223:
        factor = 4;
        break;
    case 3334:
        factor = 2;
        break;
    case 6667:
        factor = 1;
        break;
    }

    return factor;
}


int DataHandler::factorToDimension(int factor)
{
    int dimension;
    switch (factor)
    {
    case 256:
        dimension = 52;
        break;
    case 128:
        dimension = 103;
        break;
    case 64:
        dimension = 203;
        break;
    case 32:
        dimension = 393;
        break;
    case 16:
        dimension = 741;
        break;
    case 8:
        dimension = 1334;
        break;
    case 4:
        dimension = 2223;
        break;
    case 2:
        dimension = 3334;
        break;
    case 1:
        dimension = 6667;
        break;
    }

    return dimension;
}

//std::vector<std::vector<float>> DataHandler::ReadPointsFromCsv(int res)
//{
// float size = res;

// std::vector<std::vector<float>>  points(res);

// QString inputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(res) + ".csv";

// qDebug() << inputPath;

// QFile input(inputPath);

// if(!input.open(QFile::ReadOnly | QFile::Text))
// {
//     qDebug() << "File(s) do(es) not exist(s)";
//     Sampler(dimensionToFactor(res));
//     ReadPointsFromCsv(res);
// }else
// {
//     QTextStream in(&input);

//     for (int y = 0; y < size; y++) {

//         QString line = in.readLine();
//         QStringList inColumns = line.split(",");

//         for (int x = 0; x < size; x++) {

//             points.at(y).push_back( inColumns.at(x).toFloat()/1000);

//         }
//     }

//     input.close();
// }

// return points;
//}

//void DataHandler::FileOfPoints()
//{
//    QString inputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled64.csv";
//    QString outputPath = "/home/carlo/Development/PhD/C++/test64.csv";

//    QFile input(inputPath);
//    QFile output(outputPath);

//    if(!input.open(QFile::ReadOnly | QFile::Text) | !output.open(QIODevice::WriteOnly | QIODevice::Truncate))
//    {
//        qDebug() << "File(s) do(es) not exist(s)";
//    }else
//    {
//        QTextStream in(&input);
//        QTextStream out(&output);


//        for (int y = 0; y < 203; y++) {

//            QString line = in.readLine();
//            QStringList inColumns = line.split(",");

//            for (int x = 0; x < 203; x++) {

//                Constants::Vector *vec = new Constants::Vector();
//                vec->x = x;
//                vec->y = y;
//                vec->z = inColumns.at(x).toFloat();



//                out << vec->x << "," << vec->y << "," << vec->z << "\n";

//            }
//        }

//        input.close();
//        output.close();
//        qDebug() << "Done";
//    }
//}
