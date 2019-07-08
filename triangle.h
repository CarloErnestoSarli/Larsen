#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vertex.h"

/*
 *  A
 *  | \
 *  |  \
 *  |   \
 *  C--- B
 *
*/


class Triangle
{
public:
    Triangle();
    Triangle(Vertex A, Vertex B, Vertex C);
    ~Triangle();


    Vertex GetVertexA();
    void SetVertexA(Vertex &vertexA);

    Vertex GetVertexB();
    void SetVertexB(Vertex &vertexB);

    Vertex GetVertexC();
    void SetVertexC(Vertex &vertexC);

private:
    Vertex m_vertexA;
    Vertex m_vertexB;
    Vertex m_vertexC;
};

#endif // TRIANGLE_H
