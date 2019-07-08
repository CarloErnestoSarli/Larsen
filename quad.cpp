#include "quad.h"

Quad::Quad()
{

}

Quad::Quad(Vertex A, Vertex B, Vertex C, Vertex D)
{
    m_vertexA = A;
    m_vertexB = B;
    m_vertexC = C;
    m_vertexD = D;
}

Quad::~Quad()
{

}

int Quad::LookUpTable()
{
    float aZ = GetZValue(m_vertexA);
    float bZ = GetZValue(m_vertexB);
    float cZ = GetZValue(m_vertexC);
    float dZ = GetZValue(m_vertexD);

    if(aZ > 0 && bZ > 0 && cZ > 0 && dZ > 0)
    {
        return 0;

    } else if (aZ <= 0 && bZ > 0 && cZ > 0 && dZ > 0)
    {
        return 1;

    } else if (aZ > 0 && bZ <= 0 && cZ > 0 && dZ > 0)
    {
        return 2;

    } else if (aZ > 0 && bZ > 0 && cZ <= 0 && dZ > 0)
    {
        return 3;

    } else if (aZ > 0 && bZ > 0 && cZ > 0 && dZ <= 0)
    {
        return 4;

    } else
    {
        return 10;
    }
}


Vertex Quad::GetVertexA() const
{
    return m_vertexA;
}

void Quad::SetVertexA(const Vertex &vertexA)
{
    m_vertexA = vertexA;
}

Vertex Quad::GetVertexB() const
{
    return m_vertexB;
}

void Quad::SetVertexB(const Vertex &vertexB)
{
    m_vertexB = vertexB;
}

Vertex Quad::GetVertexC() const
{
    return m_vertexC;
}

void Quad::SetVertexC(const Vertex &vertexC)
{
    m_vertexC = vertexC;
}

Vertex Quad::GetVertexD() const
{
    return m_vertexD;
}

void Quad::SetVertexD(const Vertex &vertexD)
{
    m_vertexD = vertexD;
}


float Quad::GetZValue(Vertex v)
{
    float z = v.position().z();
    return z;
}


