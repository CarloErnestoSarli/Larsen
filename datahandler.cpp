#include "datahandler.h"
#include "constants.h"

#include <string>
#include <fstream>
#include <QElapsedTimer>

DataHandler::DataHandler()
{
}

DataHandler::DataHandler(int option)
{
    m_option = option;
}

void DataHandler::Sampler(int samplingFactor)
{
    QString inputPath;
    QString outputPath;

    switch (m_option) {
    case 0:
        inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_thickness.txt";
        outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(factorToDimension(samplingFactor)) + "iceThickness.csv";
        break;
    case 1:
        inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_bed.txt";
        outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(factorToDimension(samplingFactor)) + "bed.csv";
        break;
    case 2:
        inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_surface.txt";
        outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(factorToDimension(samplingFactor)) + "surface.csv";
        break;
    case 3:
        inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_icemask_grounded_and_shelves.txt";
        outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(factorToDimension(samplingFactor)) + "icemask.csv";
        break;
    }

    //     inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_rockmask.txt";

    //     inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_lakemask_vostok.txt";

    //     outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(factorToDimension(samplingFactor)) + "rockmask.csv";

    //    outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(factorToDimension(samplingFactor)) + "lakemask.csv";


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

void DataHandler::AverageSampler(int recursion)
{
    if(recursion <= 6)
    {
        QString inputPath;
        QString outputPath;

        switch (m_option) {
        case 0:
            if(recursion == 0)
            {
                inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_thickness.txt";
            }else
            {
                inputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(recursionToDimension(recursion)) + "iceThickness.csv";
            }
            outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(recursionToDimension(recursion+1)) + "iceThickness.csv";
            break;
        case 1:
            if(recursion == 0)
            {
                inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_bed.txt";
            }else
            {
                inputPath =  "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(recursionToDimension(recursion)) + "bed.csv";
            }
            outputPath=  "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(recursionToDimension(recursion+1)) + "bed.csv";
            break;
        case 2:
            if(recursion == 0)
            {
                inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_surface.txt";
            }else
            {
                inputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(recursionToDimension(recursion)) + "surface.csv";
            }
            outputPath =outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(recursionToDimension(recursion+1)) + "surface.csv";;
            break;
        case 3:
            if(recursion == 0)
            {
                inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_icemask_grounded_and_shelves.txt";
            }else
            {
                inputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(recursionToDimension(recursion)) + "icemask.csv";
            }
            outputPath =outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(recursionToDimension(recursion+1)) + "icemask.csv";
            break;
        }

        //     inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_rockmask.txt";

        //                 inputPath = "/home/carlo/Documents/bedmap2_ascii/bedmap2_lakemask_vostok.txt";


        //     outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(recursionToDimension(recursion)) + "rockmask.csv";

        //                 outputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(recursionToDimension(recursion)) + "lakemask.csv";

        QFile input(inputPath);
        QFile output(outputPath);

        if(!input.open(QFile::ReadOnly | QFile::Text) | !output.open(QFile::WriteOnly | QFile::Truncate))
        {
            qDebug() << "File(s) do(es) not exist(s)";
        }else
        {
            QTextStream in(&input);
            QTextStream out(&output);

            if(recursion == 0)
            {
                //skip header
                for(int i = 0; i < 6; i++)
                {
                    in.readLine();
                }
            }

            int z = 0;
            int fileLength = recursionToDimension(recursion)-1;

            while(!in.atEnd())
            {
                QString line;
                QString line2;

                line = in.readLine();
                line2 = in.readLine();

                QStringList inColumns;
                QStringList inColumns2;

                if(recursion == 0)
                {
                    inColumns = line.split(" ");
                    inColumns2 = line2.split(" ");
                }else {
                    inColumns = line.split(",");
                     inColumns2 = line2.split(",");
                }

                QStringList outColumns;

                int columnsNumber = inColumns.size();
                if(inColumns2.size() == columnsNumber)
                {
                    for (int x = 0; x < columnsNumber-2; ++x) {
                        QString value1= inColumns.at(x) ;
                        QString value2= inColumns.at(x+1);
                        QString value3= inColumns2.at(x);
                        QString value4= inColumns2.at(x+1);

                        if(value1 == "-9999")
                        {
                            value1 = "-1";
                        }
                        if(value2 == "-9999")
                        {
                            value2 = "-1";
                        }
                        if(value3 == "-9999")
                        {
                            value3 = "-1";
                        }
                        if(value4 == "-9999")
                        {
                            value4 = "-1";
                        }

                        if(checkStringIsDigit(value1) && checkStringIsDigit(value2) && checkStringIsDigit(value3) && checkStringIsDigit(value4))
                        {
                            float average = (value1.toInt() + value2.toInt() + value3.toInt() + value4.toInt())/4;
                            outColumns.append(QString::number(average));
                        }

                        ++x;

                    }

                    for(auto it : outColumns)
                    {
                        out << it << ",";
                    }
                    out << endl;
                }

                z++;

            }

            input.close();
            output.close();

        }

        recursion ++;
        AverageSampler(recursion);
    }

}

void DataHandler::SetOption(int option)
{
    m_option = option;
}

int DataHandler::GetOption()
{
    return m_option;
}


void DataHandler::BinFileWithNormals(int res)
{
    float normMin = 0;
    float normMax = res;
    float min = -1;
    float max = 46.21;

    QString inputPath;
    std::string outputPath;

    switch (m_option) {
    case 0:
        inputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(res) + "iceThickness.csv";
        outputPath ="/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "iceThickness.raw";
        break;
    case 1:
        inputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(res) + "bed.csv";
        outputPath ="/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "bed.raw";
        break;
    case 2:
        inputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(res) + "surface.csv";
        outputPath ="/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "surface.raw";
        break;
    case 3:
        inputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(res) + "icemask.csv";
        outputPath ="/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "icemask.raw";
        break;
    }


    //    QString inputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(res) + "rockmask.csv";

    //    QString inputPath = "/home/carlo/Development/PhD/C++/bedmap2AsciiRemovedNoDataSampled" + QString::number(res) + "lakemask.csv";

    //    std::string outputPath ="/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "rockmask.raw";

    //    std::string outputPath ="/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "lakemask.raw";


    QFile input(inputPath);
    std::ofstream output(outputPath.c_str(), std::ios::binary);

    if(!input.open(QFile::ReadOnly | QFile::Text) | !output.is_open())
    {
        qDebug() << "File(s) do(es) not exist(s)";
        Sampler(dimensionToFactor(res));
        BinFileWithNormals(res);
    }else
    {
        QTextStream in(&input);

        for (int iy = 0; iy < normMax; iy++) {

            QString line = in.readLine();
            QStringList inColumns = line.split(",");

            for (int ix = 0; ix < normMax; ix++) {

                float z = inColumns.at(ix).toFloat();
                if (z != -1)
                {
                    z = z/1000;
                }
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

    std::string inputPath;


    switch (m_option) {
    case 0:
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "iceThickness.raw";
        break;
    case 1:
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "bed.raw";
        break;
    case 2:
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "surface.raw";
        break;
    case 3:
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "icemask.raw";
        break;
    }

    //    std::string inputPath = "/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "rockmask.raw";

    //    std::string inputPath = "/home/carlo/Development/PhD/C++/Larsen/bins/sampled" + std::to_string(res) + "lakemask.raw";


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
    std::string outputPath;

    switch (m_option) {
    case 0:
        outputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "iceThickness.bin";
        break;
    case 1:
        outputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "bed.bin";
        break;
    case 2:
        outputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "surface.bin";
        break;
    case 3:
        outputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "icemask.bin";
        break;
    }

    //     outputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "rockmask.bin";

    //    outputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "lakemask.bin";

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
    std::string outputPath;
    switch (m_option) {
    case 0:
        outputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "iceThickness.bin";
        break;
    case 1:
        outputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "bed.bin";
        break;
    case 2:
        outputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "surface.bin";
        break;
    case 3:
        outputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "icemask.bin";
        break;
    }

    //    std::string outputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "rockmask.bin";

    /*    outputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "lakemask.bin"*/;

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
        inputPath  = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "iceThickness.bin";
        break;
    case 1:
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "bed.bin";
        break;
    case 2:
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "surface.bin";
        break;
    case 3:
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "icemask.bin";
        break;
    case 4:
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/vertices/vertices" + std::to_string(res) + "lakemask.bin";
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
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "iceThickness.bin";
        break;
    case 1:
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "bed.bin";
        break;
    case 2:
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "surface.bin";
        break;
    case 3:
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "icemask.bin";
        break;
    case 4:
        inputPath = "/home/carlo/Development/PhD/C++/Larsen/indeces/indeces" + std::to_string(res) + "lakemask.bin";
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


int DataHandler::recursionToDimension(int factor)
{
    int dimension;
    switch (factor)
    {
    case 7:
        dimension = 53;
        break;
    case 6:
        dimension = 104;
        break;
    case 5:
        dimension = 208;
        break;
    case 4:
        dimension = 416;
        break;
    case 3:
        dimension = 833;
        break;
    case 2:
        dimension = 1666;
        break;
    case 1:
        dimension = 3333;
        break;
    case 0:
        dimension = 6667;
        break;
    }

    return dimension;
}
