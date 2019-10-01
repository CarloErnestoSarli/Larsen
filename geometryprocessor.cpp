#include "geometryprocessor.h"

#include <QElapsedTimer>
#include <QPair>

GeometryProcessor::GeometryProcessor()
{
    o_data = new DataHandler();
    o_cMap = &o_cMap->GetColourMapObject();
}

GeometryProcessor::~GeometryProcessor()
{
    delete o_data;
}

void GeometryProcessor::CreateTriangles(int dimension, int option)
{
    o_data->SetOption(option);

    QList<QVector3D> vertList;
    std::vector<int> triIndeces;

    readPoints(dimension);
    std::vector<std::vector<float>> points = GetPoints();

    for(int y = 0; y < dimension-1; ++y)
    {
        int x = 0;
        float aZ = points[x][y];
        float bZ = points[x][y+1];
        float cZ = points[x+1][y];
        float dZ= points[x+1][y+1];

        QVector3D A (x, y, aZ);
        QVector3D B (x, y+1, bZ);
        QVector3D C (x+1, y, cZ);
        QVector3D D(x+1, y+1, dZ);

        populateArrays(A, B, C, D, vertList, triIndeces);

        readNextTwo(C, D, points, vertList, triIndeces, dimension);

    }
    SetVertList(vertList);
    SetTriIndeces(triIndeces);
}

bool GeometryProcessor::listContainsReverse(QList<QVector3D> &vertList, QVector3D vert)
{
    QListIterator<QVector3D>i(vertList);
    i.toBack();
    int movingAway = 0;
    float previousDistance = 0;
    while (i.hasPrevious() && movingAway <= 6)
    {
        float currentDistance =i.previous().distanceToPoint(vert);

        if(currentDistance == 0)
        {
            return  true;
        }else
        {
            if(currentDistance > previousDistance)
            {
                movingAway++;
                previousDistance = currentDistance;
            }
        }

//        if(i.previous() == vert){
//            return true;
//        }
    }
    return false;
}

int GeometryProcessor::listIndexReverse(QList<QVector3D> &vertList, QVector3D vert)
{
    QListIterator<QVector3D>i(vertList);
    i.toBack();
    int index =  vertList.length();

    while (i.hasPrevious())
    {
        if(i.previous() == vert){
            return index-1;
        }
        index--;
    }
}

void GeometryProcessor::generateIndecesVerteces(QVector3D &A, QVector3D &B, QVector3D &C )
{
    QList<QVector3D> vertList = GetVertList();
    std::vector<int> triIndeces = GetTriIndeces();

}

void GeometryProcessor::readNextTwo(QVector3D &A, QVector3D &B, std::vector<std::vector<float>> &points, QList<QVector3D> &vertList, std::vector<int> &triIndeces, int c )
{
    float x = A.x();
    float y = A.y();
    float cZ = points[x+1][y];
    float dZ= points[x+1][y+1];
    QVector3D C (x+1, y, cZ);
    QVector3D D(x+1, y+1, dZ);

    populateArrays(A,B,C,D, vertList, triIndeces);

    if(x+2 < c)
    {
        readNextTwo(C, D, points, vertList, triIndeces, c);
    }

}

void GeometryProcessor::populateArrays(QVector3D &A, QVector3D &B, QVector3D &C, QVector3D &D, QList<QVector3D> &vertList, std::vector<int> &triIndeces )
{
    float aZ = A.z();
    float bZ = B.z();
    float cZ = C.z();
    float dZ = D.z();

    int triType = checkForTriangles(aZ, bZ, cZ, dZ);

    switch (triType) {
    case 0:
        //no triangle
        break;
    case 1:
        //adc
        addVerticesandIndeces(A, D, C, vertList, triIndeces);
         //adb
        addVerticesandIndeces(A, D, B, vertList, triIndeces);
        break;
    case 2:
        //bcd
        addVerticesandIndeces(B, C, D, vertList, triIndeces);
        break;
    case 3:
        //acd
        addVerticesandIndeces(A, C, D, vertList, triIndeces);
        break;
    case 4:
        //abd
        addVerticesandIndeces(A, B, D, vertList, triIndeces);
        break;
    case 5:
        //abc
        addVerticesandIndeces(A, B, C, vertList, triIndeces);
        break;
    }
}

int GeometryProcessor::checkForTriangles(float &aZ, float &bZ, float &cZ, float &dZ)
{
    if(aZ <= 0 && bZ <= 0 && cZ <= 0 && dZ <= 0)
    {
        return 0;

    } else if (aZ > 0 && bZ > 0 && cZ > 0 && dZ > 0)
    {
        return 1;

    } else if (aZ <=0 && bZ > 0 && cZ > 0 && dZ > 0)
    {
        return 2;

    } else if (aZ > 0 && bZ <= 0 && cZ > 0 && dZ > 0)
    {
        return 3;

    } else if (aZ > 0 && bZ > 0 && cZ <= 0 && dZ > 0)
    {
        return 4;

    } else if (aZ > 0 && bZ > 0 && cZ > 0 && dZ <= 0)
    {
        return 5;
    }
}

void GeometryProcessor::addVerticesandIndeces(QVector3D &A, QVector3D &B, QVector3D &C, QList<QVector3D> &vertList, std::vector<int> &triIndeces)
{
    if(listContainsReverse(vertList, A))
    {
    }else
    {
        vertList.append(A);
    }
    if(listContainsReverse(vertList, B))
    {
    }else
    {
        vertList.append(B);
    }
    if(listContainsReverse(vertList, C))
    {
    }else
    {
        vertList.append(C);
    }


    triIndeces.push_back(listIndexReverse(vertList, A));
    triIndeces.push_back(listIndexReverse(vertList, B));
    triIndeces.push_back(listIndexReverse(vertList, C));
}

void GeometryProcessor::readPoints(int dimension)
{
    QElapsedTimer timer;
    timer.start();

    SetPoints(o_data->ReadPointsFromBinary(dimension));

    qDebug() << "The readPoints func took" << timer.elapsed() << "milliseconds";
}



//////////////////ACCESSORS////////////////

void GeometryProcessor::SetPoints(std::vector<std::vector<float> > points)
{
    m_points = points;
}

std::vector<std::vector<float>> GeometryProcessor::GetPoints()
{
    return m_points;
}


std::vector<int> GeometryProcessor::GetTriIndeces()
{
    return m_triIndeces;
}

void GeometryProcessor::SetTriIndeces(std::vector<int> triIndeces)
{
    m_triIndeces = triIndeces;
}

std::vector<Vertex> GeometryProcessor::GetTriVertices()
{
    return m_triVertices;
}

void GeometryProcessor::SetTriVertices(std::vector<Vertex> triVertices)
{
    m_triVertices = triVertices;
}

std::vector<Triangle> GeometryProcessor::GetTriangles()
{
    return m_triangles;
}

void GeometryProcessor::SetTriangles(std::vector<Triangle> triangles)
{
    m_triangles = triangles;
}

std::vector<Quad> GeometryProcessor::GetQuads()
{
    return m_quads;
}

void GeometryProcessor::SetQuads(std::vector<Quad> quads)
{
    m_quads = quads;
}


QSet<QVector3D> GeometryProcessor::GetVertSet()
{
    return m_vertSet;
}

void GeometryProcessor::SetVertSet(QSet<QVector3D> vertSet)
{
    m_vertSet = vertSet;
}

QList<QVector3D> GeometryProcessor::GetVertList()
{
    return m_vertList;
}

void GeometryProcessor::SetVertList(QList<QVector3D> vertList)
{
    m_vertList = vertList;
}


