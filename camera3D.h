#ifndef CAMERA_H
#define CAMERA_H

#include "transform3D.h"
#include <QQuaternion>
#include <QMatrix4x4>
#include <QVector3D>

class Camera3D
{
public:

    // Constants
    static const QVector3D LocalForward;
    static const QVector3D LocalUp;
    static const QVector3D LocalRight;

    // Constructors
    Camera3D();

    // Transform By (Add/Scale)
    void translate(const QVector3D &dt);
    void translate(float dx, float dy, float dz);
    void rotate(const QQuaternion &dr);
    void rotate(float angle, const QVector3D &axis);
    void rotate(float angle, float ax, float ay, float az);

    // Transform To (Setters)
    void SetTranslation(const QVector3D &t);
    void SetTranslation(float x, float y, float z);
    void SetRotation(const QQuaternion &r);
    void SetRotation(float angle, const QVector3D &axis);
    void SetRotation(float angle, float ax, float ay, float az);
    /**
     * @brief Setter for the default view matrix.
     * @param defaultView The QMatrix4x4 to be used as the default view.
     */
    void SetDefaultView(QMatrix4x4 defaultView);

    /**
     * @brief Sets the rotation quaternion to the identity quaternion.
     */
    void ResetRotation();

    /**
     * @brief Sets the translation to zero.
     */
    void ResetTranslation(float x, float y, float z);

    /**
     * @brief Sets the camera position and orientation to the default.
     */
    void ResetView(float x, float y, float z);


    // Accessors
    const QVector3D& translation() const;
    const QQuaternion& rotation() const;
    const QMatrix4x4& toMatrix();

    // Queries
    QVector3D forward() const;
    QVector3D right() const;
    QVector3D up() const;

private:
    bool m_dirty;
    QVector3D m_translation;
    QQuaternion m_rotation;
    QMatrix4x4 m_world;
    /**
     * @brief Matrix describing the default camera view.
     */
    QMatrix4x4 m_DefaultView;

#ifndef QT_NO_DATASTREAM
    friend QDataStream &operator<<(QDataStream &out, const Camera3D &transform);
    friend QDataStream &operator>>(QDataStream &in, Camera3D &transform);
#endif
};

Q_DECLARE_TYPEINFO(Camera3D, Q_MOVABLE_TYPE);

// Constructors
inline Camera3D::Camera3D() : m_dirty(true) {}

// Transform By (Add/Scale)
inline void Camera3D::translate(float dx, float dy,float dz) { translate(QVector3D(dx, dy, dz)); }
inline void Camera3D::rotate(float angle, const QVector3D &axis) { rotate(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Camera3D::rotate(float angle, float ax, float ay,float az) { rotate(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }

// Transform To (Setters)
inline void Camera3D::SetTranslation(float x, float y, float z) { SetTranslation(QVector3D(x, y, z)); }
inline void Camera3D::SetRotation(float angle, const QVector3D &axis) { SetRotation(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Camera3D::SetRotation(float angle, float ax, float ay, float az) { SetRotation(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }

// Accessors
inline const QVector3D& Camera3D::translation() const { return m_translation; }
inline const QQuaternion& Camera3D::rotation() const { return m_rotation; }

// Qt Streams
#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const Camera3D &transform);
#endif

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &out, const Camera3D &transform);
QDataStream &operator>>(QDataStream &in, Camera3D &transform);
#endif

#endif // CAMERA_H
