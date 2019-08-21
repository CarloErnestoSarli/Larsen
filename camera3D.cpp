#include "camera3D.h"
#include <QDebug>

const QVector3D Camera3D::LocalForward(0.0f, 0.0f, -1.0f);
const QVector3D Camera3D::LocalUp(0.0f, 10.0f, 0.0f);
const QVector3D Camera3D::LocalRight(1.0f, 0.0f, 0.0f);

void Camera3D::SetDefaultView(QMatrix4x4 defaultView)
{
    m_DefaultView = defaultView;
}

// Transform By (Add/Scale)
void Camera3D::translate(const QVector3D &dt)
{
    m_dirty = true;
    m_translation += dt;
}

void Camera3D::rotate(const QQuaternion &dr)
{
    m_dirty = true;
    m_rotation = dr * m_rotation;
}

// Transform To (Setters)
void Camera3D::SetTranslation(const QVector3D &t)
{
    m_dirty = true;
    m_translation = t;
}

void Camera3D::SetRotation(const QQuaternion &r)
{
    m_dirty = true;
    m_rotation = r;
}

// Accessors
const QMatrix4x4 &Camera3D::toMatrix()
{
    if (m_dirty)
    {
        m_dirty = false;
        m_world.setToIdentity();
        m_world.rotate(m_rotation.conjugate());
        m_world.translate(-m_translation);
    }
    return m_world;
}

void Camera3D::ResetRotation()
{
    QQuaternion zero(1,0,0,0);
    SetRotation(zero);
}

void Camera3D::ResetTranslation(float x, float y, float z)
{
    QVector3D zero(x,y,z);
    SetTranslation(zero);
}

void Camera3D::ResetView(float x, float y, float z)
{
    ResetRotation();
    ResetTranslation(x,y,z);
}

// Queries
QVector3D Camera3D::forward() const
{
    return m_rotation.rotatedVector(LocalForward);
}

QVector3D Camera3D::right() const
{
    return m_rotation.rotatedVector(LocalRight);
}

QVector3D Camera3D::up() const
{
    return m_rotation.rotatedVector(LocalUp);
}

// Qt Streams
QDebug operator<<(QDebug dbg, const Camera3D &transform)
{
    dbg << "Camera3D\n{\n";
    dbg << "Position: <" << transform.translation().x() << ", " << transform.translation().y() << ", " << transform.translation().z() << ">\n";
    dbg << "Rotation: <" << transform.rotation().x() << ", " << transform.rotation().y() << ", " << transform.rotation().z() << " | " << transform.rotation().scalar() << ">\n}";
    return dbg;
}

QDataStream &operator<<(QDataStream &out, const Camera3D &transform)
{
    out << transform.m_translation;
    out << transform.m_rotation;
    return out;
}

QDataStream &operator>>(QDataStream &in, Camera3D &transform)
{
    in >> transform.m_translation;
    in >> transform.m_rotation;
    transform.m_dirty = true;
    return in;
}
