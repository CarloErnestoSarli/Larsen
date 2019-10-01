/**
 * @file camera3D.h
 * @author Carlo Sarli
 * @date 30 August 2019
 * @brief This class provides Camera functionalty for  the canvas.
 *
 * Detailed description goes here.
 */

#ifndef GEOMETRYPROCESSOR_H
#define GEOMETRYPROCESSOR_H

#include <QSet>
#include <QList>
#include <QHash>
#include <QVector3D>

#include "colourmap.h"
#include "datahandler.h"
#include "vertex.h"
#include "quad.h"
#include "triangle.h"



class GeometryProcessor
{
public:
    GeometryProcessor();
    ~GeometryProcessor();

    void SetPoints(std::vector<std::vector<float>> points);
    std::vector<std::vector<float>> GetPoints();


    void GenerateTriangles();
    void GenerateQuads(int dimension);

    std::vector<int> GetTriIndeces();
    void SetTriIndeces(std::vector<int> triIndeces);

    std::vector<Vertex> GetTriVertices();
    void SetTriVertices(std::vector<Vertex> triVertices);

    std::vector<Triangle> GetTriangles();
    void SetTriangles(std::vector<Triangle> triangles);

    std::vector<Quad> GetQuads();
    void SetQuads( std::vector<Quad> quads);

    QSet<Vertex> GetVertSet();
    void SetVertSet(QSet<Vertex> vertSet);

    void SetUpVertices();
    void SetUpIndeces();
    QList<Vertex> GetVertList();
    void SetVertList(QList<Vertex> vertList);

    void CreateTriangles(int dimension, int option);

private:
    std::vector<std::vector<float>> m_points;
    std::vector<Quad> m_quads;
    std::vector<Triangle> m_triangles;
    std::vector<Vertex> m_triVertices;
    std::vector<int> m_triIndeces;
    QSet<Vertex> m_vertSet;
    QList<Vertex> m_vertList;

    DataHandler *o_data;
    ColourMap *o_cMap;

    void readPoints(int dimension);
    Vertex generateVertexFromCoord(float x, float y, float z);
    Quad readQuad(float x, float y, std::vector<std::vector<float> > points);
    void readTriangle(Quad q, int type, std::vector<Triangle> &triangles);
    bool listContainsReverse(QList<Vertex> &vertList, Vertex vert);
    int listIndexReverse(QList<Vertex> &vertList, Vertex vert);
    int checkForTriangles(float &aZ, float &bZ, float &cZ, float &dZ);
    void addVerticesandIndeces(Vertex &A, Vertex &B, Vertex &C, QList<Vertex> &vertList, std::vector<int> &triIndeces);
    void populateArrays(QVector3D &A, QVector3D &B, QVector3D &C, QVector3D &D, QList<Vertex> &vertList, std::vector<int> &triIndeces);
    void readNextTwo(QVector3D &A, QVector3D &B, std::vector<std::vector<float> > &points, QList<Vertex> &vertList, std::vector<int> &triIndeces, int c);
    void generateIndecesVerteces(QVector3D &A, QVector3D &B, QVector3D &C);
};

#endif // GEOMETRYPROCESSOR_H
