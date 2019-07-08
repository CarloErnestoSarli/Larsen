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

    std::vector<Vertex> GetTriVerteces();
    void SetTriVerteces(std::vector<Vertex> triVerteces);

    std::vector<int> GetTriIndeces();
    void SetTriIndeces(std::vector<int> triIndeces);

    QColor GetBgColour() ;
    void SetBgColour(QColor bgColour);

    int GetProgressValue();
    void SetProgressValue(int progressValue);

    QString GetProgressStatus();
    void SetProgressStatus(QString progressStatus);

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
    std::vector<Vertex> m_triVerteces;
    std::vector<int> m_triIndeces;

    QOpenGLBuffer m_triVertex;
    QOpenGLBuffer *m_triIndex = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    QOpenGLBuffer m_quadVertex;
    QOpenGLBuffer m_quadIndex;

    QOpenGLVertexArrayObject m_triangleVAO;
    QOpenGLVertexArrayObject m_quadVAO;

    QOpenGLShaderProgram *m_program;

    // Shader Information
    int u_modelToWorld;
    int u_worldToCamera;
    int u_cameraToView;
    QMatrix4x4 m_projection;
    Camera3D m_camera;
    Transform3D m_transform;

    int m_drawOption;
    int m_resOption;
    int m_pointSizeOption;
    int m_progressValue;
    QString m_progressStatus;

    QPointF normaliseMouseCoord(QPoint p);
    void mouseMoveEvent(QMouseEvent *event);

    void drawFigure();
    void setUpTriangles(int dimension);
    void initializeVertices();

    void updateProgressBar(int value, QString label);
    void updateTrianglesLabel(QString label);

signals:
    void Si_SetProgressBarValue(int value);
    void Si_SetProgressBarLabel(QString label);
    void Si_SetTrianglesLabel(QString label);

protected slots:
    void update();

public slots:
    void S_GetDrawOption(int option);
    void S_GetResOption(int option);
    void S_GetBgOption(int option);
    void S_GetPointSizeOption(int option);

};

#endif // CANVAS_H
