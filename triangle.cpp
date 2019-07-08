#include "triangle.h"

Triangle::Triangle()
{

}

Triangle::Triangle(Vertex A, Vertex B, Vertex C)
{
    m_vertexA = A;
    m_vertexB = B;
    m_vertexC = C;
}

Triangle::~Triangle()
{

}

Vertex Triangle::GetVertexA()
{
    return m_vertexA;
}

void Triangle::SetVertexA( Vertex &vertexA)
{
    m_vertexA = vertexA;
}

Vertex Triangle::GetVertexB()
{
    return m_vertexB;
}

void Triangle::SetVertexB( Vertex &vertexB)
{
    m_vertexB = vertexB;
}

Vertex Triangle::GetVertexC()
{
    return m_vertexC;
}

void Triangle::SetVertexC( Vertex &vertexC)
{
    m_vertexC = vertexC;
}
