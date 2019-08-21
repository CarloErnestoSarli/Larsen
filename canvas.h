#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include <QVector3D>

#include "transform3D.h"
#include "camera3D.h"
#include "geometryprocessor.h"

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void SetDrawOption(int option);
    int GetDrawOption();
    void SetResOption(int option);
    int GetResOption();
    void SetPointSizeOption(int option);
    int GetPointSizeOption();

    std::vector<Vertex> GetIceVerteces();
    void SetIceVerteces(std::vector<Vertex> triVerteces);

    std::vector<int> GetIceIndeces();
    void SetIceIndeces(std::vector<int> triIndeces);

    std::vector<Vertex> GetBedVerteces();
    void SetBedVerteces(std::vector<Vertex> triVerteces);

    std::vector<int> GetBedIndeces();
    void SetBedIndeces(std::vector<int> triIndeces);

    std::vector<Vertex> GetSurfaceVerteces();
    void SetSurfaceVerteces(std::vector<Vertex> triVerteces);

    std::vector<int> GetSurfaceIndeces();
    void SetSurfaceIndeces(std::vector<int> triIndeces);

    QColor GetBgColour() ;
    void SetBgColour(QColor bgColour);

    int GetProgressValue();
    void SetProgressValue(int progressValue);

    QString GetProgressStatus();
    void SetProgressStatus(QString progressStatus);

    void SetLastX(float LastX);
    void SetLastY(float LastY);

    int GetZFactorOption();
    void SetZFactorOption(int option);

    int GetZOffsetOption();
    void SetZOffsetOption(int option);

    bool GetIceSurfaceToggled() const;
    void SetIceSurfaceToggled(bool iceSurfaceToggled);

    bool GetBedSurfaceToggled() const;
    void SetBedSurfaceToggled(bool bedSurfaceToggled);

    bool GetSurfaceSurfaceToggled() const;
    void SetSurfaceSurfaceToggled(bool surfaceSurfaceToggled);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    virtual void tearDownGL();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QColor m_bgColour;
    std::vector<Vertex> m_iceVerteces;
    std::vector<int> m_iceIndeces;
    std::vector<Vertex> m_bedVerteces;
    std::vector<int> m_bedIndeces;
    std::vector<Vertex> m_surfaceVerteces;
    std::vector<int> m_surfaceIndeces;

    QOpenGLBuffer m_iceVertex;
    QOpenGLBuffer *m_iceIndex = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    QOpenGLBuffer m_bedVertex;
    QOpenGLBuffer *m_bedIndex = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    QOpenGLBuffer m_surfaceVertex;
    QOpenGLBuffer *m_surfaceIndex = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    QOpenGLVertexArrayObject m_iceVAO;
    QOpenGLVertexArrayObject m_bedVAO;
    QOpenGLVertexArrayObject m_surfaceVAO;

    QOpenGLShaderProgram *m_program;

    // Shader Information
    int u_modelToWorld;
    int u_worldToCamera;
    int u_cameraToView;
    QMatrix4x4 m_projection;
    Camera3D m_camera;
    Transform3D m_transform;

    /**
     * @brief The X position of the mouse at the beginning of a movement event.
     */
    float m_LastX;

    /**
     * @brief The Y position of the mouse at the beginning of a movement event.
     */
    float m_LastY;

    int m_drawOption;
    int m_resOption;
    int m_pointSizeOption;
    int m_zFactorOption;
    int m_zOffsetOption;
    int m_progressValue;
    bool m_iceSurfaceToggled;
    bool m_bedSurfaceToggled;
    bool m_surfaceSurfaceToggled;

    QString m_progressStatus;

    void drawFigure(int option);
    void setUpTriangles(int dimension);
    void initializeVertices();

    void updateProgressBar(int value, QString label);
    void updateTrianglesLabel(QString label, int option);

    void loadBuffers();

    //FILTHY DUPLICATE FROM DATA HANDLER
    int calculateZoomSpeed(int dimension);


    void wheelEvent(QWheelEvent *event);
signals:
    void Si_SetProgressBarValue(int value);
    void Si_SetProgressBarLabel(QString label);
    void Si_SetIceTrianglesLabel(QString label);
    void Si_SetBedTrianglesLabel(QString label);
    void Si_SetSurfaceTrianglesLabel(QString label);

protected slots:
    void update();

public slots:
    void S_GetDrawOption(int option);
    void S_GetResOption(int option);
    void S_GetBgOption(int option);
    void S_GetPointSizeOption(int option);  
    void S_GetZFactorOption(int option);
    void S_GetIceSurfaceToggle(bool toggle);
    void S_GetBedSurfaceToggle(bool toggle);
    void S_GetSurfaceSurfaceToggle(bool toggle);
    void S_GetZOffsetOption(int option);
};

#endif // CANVAS_H
