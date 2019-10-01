/**
 * @file camera3D.h
 * @author Trent Reed, Carlo Sarli
 * @date 30 August 2019
 * @brief This class provides Camera functionalty for  the canvas.
 *
 * The camera class handles the implementation of the camera in 3D space
 */

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
    /**
     * @brief Base movement forward (z).
     */
    static const QVector3D LocalForward;
    /**
     * @brief Base movement up (y).
     */
    static const QVector3D LocalUp;
    /**
     * @brief Base movement to the right (x).
     */
    static const QVector3D LocalRight;

    // Constructors
    Camera3D();

    // Transform By (Add/Scale)
    /**
     * @brief Translate the camera.
     * @param QVector3D containing the translation
     */
    void translate(const QVector3D &dt);
    /**
     * @brief Translate the camera overload.
     * @param x,y,z value for the translation
     */
    void translate(float dx, float dy, float dz);
    /**
     * @brief Rotates camera by the rotation quaternion.
     * @paragraph QQuaternion containing the rotation values
     */
    void rotate(const QQuaternion &dr);
    /**
     * @brief Rotates camera by the rotation vector for the camera.
     * @param angle, rotation angle
     * @param QVector3D containing the values of rotation on the axis
     */
    void rotate(float angle, const QVector3D &axis);
    /**
     * @brief Rotates camera by the rotation coordinates and angle for the camera.
     * @param angle, as the rotation angle
     * @param x,y,z values for the translation
     */
    void rotate(float angle, float ax, float ay, float az);

    // Transform To (Setters)
    /**
     * @brief Sets the translation for the camera.
     * @param QVector3D the value of the translation along the axis
     */
    void SetTranslation(const QVector3D &t);
    /**
     * @brief Sets the translation for the camera overload.
     * @param x,y,z values for the translation along the axis
     */
    void SetTranslation(float x, float y, float z);
    /**
     * @brief Sets the rotation quaternion to the identity quaternion.
     * @param QQuaternion, the values plus angle of the rotation
     */
    void SetRotation(const QQuaternion &r);
    /**
     * @brief Sets the rotation Vector and angle.
     * @param angle, the rotation angle
     * @param QVector3D the x,y,z vector for the rotation
     */
    void SetRotation(float angle, const QVector3D &axis);
    /**
     * @brief Sets the rotation values individually.
     * @param angle, the rotation angle
     * @param x,y,z the axis values
     */
    void SetRotation(float angle, float ax, float ay, float az);
    /**
     * @brief Setter for the default view matrix.
     * @param defaultView The QMatrix4x4 to be used as the default view.
     */
    void SetDefaultView(QMatrix4x4 defaultView);

    /**
     * @brief Resets the rotation to default values.
     */
    void ResetRotation();

    /**
     * @brief  Resets the translation to the given values.
     * @param x,y,z the values to reset the translation to on the coord system
     */
    void ResetTranslation(float x, float y, float z);

    /**
     * @brief  Resets the view to the given values.
     * @param x,y,z the values to reset the view to on the coord system
     */
    void ResetView(float x, float y, float z);


    // Accessors
    /**
     * @brief Gets translation vector.
     * @returns QVector3D the translation value
     */
    const QVector3D& translation() const;
    /**
     * @brief Gets rotation quaternion.
     * @returns QQuaternion the rotation quaternion
     */
    const QQuaternion& rotation() const;
    /**
     * @brief Gets world view values.
     * @returns QMatrix4x4 the composed matrix from value
     */
    const QMatrix4x4& toMatrix();

    // Queries
    /**
     * @brief Moves the camera forward.
     * @returns QVector3D the forward value
     */
    QVector3D forward() const;
    /**
     * @brief Moves the camera right.
     * @returns QVector3D the right value
     */
    QVector3D right() const;
    /**
     * @brief Moves the camera up
     * @returns QVector3D the up value
     */
    QVector3D up() const;

private:
    /**
     * @brief value to determine if the camera has been moved.
     */
    bool m_dirty;
    /**
     * @brief The translation value.
     */
    QVector3D m_translation;
    /**
     * @brief The rotation value.
     */
    QQuaternion m_rotation;
    /**
     * @brief The world view matrix.
     */
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
