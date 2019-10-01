/**
 * @file camera3D.h
 * @author Trent Reed, Carlo Sarli
 * @date 30 August 2019
 * @brief This class provides Camera functionalty for  the canvas.
 *
 * Detailed description goes here.
 */

#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>

class Vertex
{
public:
  // Constructors
  Q_DECL_CONSTEXPR Vertex();
  Q_DECL_CONSTEXPR explicit Vertex(const QVector3D &position);
  Q_DECL_CONSTEXPR Vertex(const QVector3D &position, const QVector3D &normal);

  // Accessors / Mutators
  Q_DECL_CONSTEXPR const QVector3D& position() const;
  Q_DECL_CONSTEXPR const QVector3D& normal() const;
  void setPosition(const QVector3D& position);
  void setNormal(const QVector3D& normal);

  // OpenGL Helpers
  static const int PositionTupleSize = 3;
  static const int NormalTupleSize = 3;
  static Q_DECL_CONSTEXPR int positionOffset();
  static Q_DECL_CONSTEXPR int normalOffset();
  static Q_DECL_CONSTEXPR int stride();

private:
  QVector3D m_position;
  QVector3D m_normal;

};

/*******************************************************************************
 * Inline Implementation
 ******************************************************************************/

// Note: Q_MOVABLE_TYPE means it can be memcpy'd.
Q_DECLARE_TYPEINFO(Vertex, Q_MOVABLE_TYPE);

// Constructors
Q_DECL_CONSTEXPR inline Vertex::Vertex() {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector3D &position) : m_position(position) {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector3D &position, const QVector3D &normal) : m_position(position), m_normal(normal) {}

// Accessors / Mutators
Q_DECL_CONSTEXPR inline const QVector3D& Vertex::position() const { return m_position; }
Q_DECL_CONSTEXPR inline const QVector3D& Vertex::normal() const { return m_normal; }
void inline Vertex::setPosition(const QVector3D& position) { m_position = position; }
void inline Vertex::setNormal(const QVector3D& normal) { m_normal = normal; }

// OpenGL Helpers
Q_DECL_CONSTEXPR inline int Vertex::positionOffset() { return offsetof(Vertex, m_position); }
Q_DECL_CONSTEXPR inline int Vertex::normalOffset() { return offsetof(Vertex, m_normal); }
Q_DECL_CONSTEXPR inline int Vertex::stride() { return sizeof(Vertex); }

#endif // VERTEX_H
