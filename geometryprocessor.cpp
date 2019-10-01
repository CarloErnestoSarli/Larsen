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

    QList<Vertex> vertList;
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

bool GeometryProcessor::listContainsReverse(QList<Vertex> &vertList, Vertex vert)
{  
    QListIterator<Vertex>i(vertList);
    i.toBack();
    int movingAway = 0;
    float previousDistance = 0;
    while (i.hasPrevious() && movingAway <= 6)
    {
        float currentDistance =i.previous().position().distanceToPoint(vert.position());

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

int GeometryProcessor::listIndexReverse(QList<Vertex> &vertList, Vertex vert)
{
    QListIterator<Vertex>i(vertList);
    i.toBack();
    int index =  vertList.length();

    while (i.hasPrevious())
    {
        if(i.previous().position() == vert.position()){
            return index-1;
        }
        index--;
    }
}

void GeometryProcessor::generateIndecesVerteces(QVector3D &A, QVector3D &B, QVector3D &C )
{
    QList<Vertex> vertList = GetVertList();
    std::vector<int> triIndeces = GetTriIndeces();

}

void GeometryProcessor::readNextTwo(QVector3D &A, QVector3D &B, std::vector<std::vector<float>> &points, QList<Vertex> &vertList, std::vector<int> &triIndeces, int c )
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

void GeometryProcessor::populateArrays(QVector3D &a, QVector3D &b, QVector3D &c, QVector3D &d, QList<Vertex> &vertList, std::vector<int> &triIndeces )
{
    float aZ = a.z();
    float bZ = b.z();
    float cZ = c.z();
    float dZ = d.z();

    int triType = checkForTriangles(aZ, bZ, cZ, dZ);

    QVector3D normal;
    Vertex A;
    Vertex B;
    Vertex C;
    Vertex D;

    switch (triType) {
    case 0:
        //no triangle
        break;
    case 1:

        //adc
        normal = QVector3D::crossProduct(d-a, c-d).normalized();
        A = Vertex (a, normal);
        D = Vertex (d, normal);
        C = Vertex (c, normal);
        addVerticesandIndeces(A, D, C, vertList, triIndeces);
         //adb
        normal = QVector3D::crossProduct(d-a, b-d).normalized();
        A = Vertex (a, normal);
        D = Vertex (d, normal);
        B = Vertex (b, normal);
        addVerticesandIndeces(A, D, B, vertList, triIndeces);
        break;
    case 2:
        //bcd
        normal = QVector3D::crossProduct(c-b, d-c).normalized();
        B = Vertex (b, normal);
        C = Vertex (c, normal);
        D = Vertex (d, normal);
        addVerticesandIndeces(B, C, D, vertList, triIndeces);
        break;
    case 3:
        //acd
        normal = QVector3D::crossProduct(c-a, d-c).normalized();
        A = Vertex (a, normal);
        C = Vertex (c, normal);
        D = Vertex (d, normal);
        addVerticesandIndeces(A, C, D, vertList, triIndeces);
        break;
    case 4:
        //abd
        normal = QVector3D::crossProduct(b-a, d-b).normalized();
        A = Vertex (a, normal);
        B = Vertex (b, normal);
        D = Vertex (d, normal);
        addVerticesandIndeces(A, B, D, vertList, triIndeces);
        break;
    case 5:
        //abc
        normal = QVector3D::crossProduct(b-a, c-b).normalized();
        A = Vertex (a, normal);
        B = Vertex (b, normal);
        C = Vertex (c, normal);
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

void GeometryProcessor::addVerticesandIndeces(Vertex &A, Vertex &B, Vertex &C, QList<Vertex> &vertList, std::vector<int> &triIndeces)
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


QSet<Vertex> GeometryProcessor::GetVertSet()
{
    return m_vertSet;
}

void GeometryProcessor::SetVertSet(QSet<Vertex> vertSet)
{
    m_vertSet = vertSet;
}

QList<Vertex> GeometryProcessor::GetVertList()
{
    return m_vertList;
}

void GeometryProcessor::SetVertList(QList<Vertex> vertList)
{
    m_vertList = vertList;
}


