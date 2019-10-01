/**
 * @file camera3D.h
 * @author Carlo Sarli
 * @date 30 August 2019
 * @brief This class provides Camera functionalty for  the canvas.
 *
 * Detailed description goes here.
 */

#ifndef QUAD_H
#define QUAD_H

#include "vertex.h"

/*
 *  A-------B
 *  |       |
 *  |       |
 *  |       |
 *  D-------C
 *
 *
 *
*/

class Quad
{
public:
    Quad();
    Quad(Vertex A, Vertex B, Vertex C, Vertex D);
    ~Quad();

    float GetZValue(Vertex v);
    int LookUpTable();

    Vertex GetVertexA() const;
    void SetVertexA(const Vertex &vertexA);

    Vertex GetVertexB() const;
    void SetVertexB(const Vertex &vertexB);

    Vertex GetVertexC() const;
    void SetVertexC(const Vertex &vertexC);

    Vertex GetVertexD() const;
    void SetVertexD(const Vertex &vertexD);

private:
    Vertex m_vertexA;
    Vertex m_vertexB;
    Vertex m_vertexC;
    Vertex m_vertexD;



};

#endif // QUAD_H
