#include "canvas.h"
#include "vertex.h"
#include "userinput.h"
#include "datahandler.h"
#include "constants.h"
#include "quad.h"
#include "triangle.h"

#include <stdlib.h>
#include <stdio.h>
#include <QHash>
#include <QHashFunctions>
#include <QLocale>


const float Constants::MIN_THICKNESS = -1;
const float Constants::MAX_THICKNESS = 4.621;
GeometryProcessor *setUp;

DataHandler *o_data = new DataHandler();
ColourMap *o_cMap = &o_cMap->GetColourMapObject();

Canvas::Canvas(QWidget *parent) : QOpenGLWidget(parent)
{
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    m_transform.translate(0, 0, 0);
    m_drawOption = 0;
    m_resOption = 52;
    m_pointSizeOption = 5;
    m_zFactorOption = 1;
    m_zOffsetOption = 1;
    m_iceSurfaceToggled = false;
    m_bedSurfaceToggled = false;
    m_surfaceSurfaceToggled = false;
    m_icemaskSurfaceToggled = false;
    m_rockmaskSurfaceToggled = false;
    m_samplingOption = 0;
    m_iceThicknessMapSelection = 0;
    m_bedMapSelection = 0;
    m_lightingSelection = 0;

    m_lightPosition = QVector3D(1.2f, 1.0f, 2.0f);
    m_lightColour = QVector3D(1.0f, 1.0f, 1.0f);

    setUp = new GeometryProcessor();
    SetBgColour(Qt::gray);
    m_camera.ResetView(m_resOption/2,m_resOption/2, m_resOption*1.5);
    m_transform.ResetTransform();

}

Canvas::~Canvas()
{
    delete setUp;
    //delete [] vertices;
}

/////////////SETUP/////////////////
void Canvas::initializeGL()
{
    // Initialize OpenGL Backend
    initializeOpenGLFunctions();
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

    // Set global information
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_PROGRAM_POINT_SIZE);


    //    QColor bgColour = GetBgColour();
    //    glClearColor(bgColour.redF(),bgColour.greenF(),bgColour.blueF(),bgColour.alphaF());

    // Application-specific initialization
    {
        // Create Shader (Do not release until VAO is created)
        m_program = new QOpenGLShaderProgram();
        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
        m_program->link();
        m_program->bind();

        // Cache Uniform Locations
        u_modelToWorld = m_program->uniformLocation("modelToWorld");
        u_worldToCamera = m_program->uniformLocation("worldToCamera");
        u_cameraToView = m_program->uniformLocation("cameraToView");


        // Create Vertex Array Object (VAO)
        m_iceVAO.create();
        m_iceVAO.bind();

        // Create Buffer (Do not release until VAO is created)
        m_iceVertex.create();
        m_iceVertex.bind();
        m_iceVertex.setUsagePattern(QOpenGLBuffer::StaticDraw);

        m_iceIndex->create();
        m_iceIndex->bind();
        m_iceIndex->setUsagePattern(QOpenGLBuffer::StaticDraw);

        m_program->enableAttributeArray(0);
        m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());

        m_program->enableAttributeArray(1);
        m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::normalOffset(), Vertex::NormalTupleSize, Vertex::stride());

        m_program->enableAttributeArray(2);
        m_program->setAttributeBuffer(2, GL_INT, 0, 3, sizeof(int));

        m_program->enableAttributeArray(3);
        m_program->setAttributeBuffer(3, GL_FLOAT, 0, 2);


        // Release (unbind) all

        m_iceVertex.release();
        m_iceIndex->release();
        m_iceVAO.release();

        // Create Vertex Array Object (VAO)
        m_bedVAO.create();
        m_bedVAO.bind();

        m_bedVertex.create();
        m_bedVertex.bind();
        m_bedVertex.setUsagePattern(QOpenGLBuffer::StaticDraw);

        m_bedIndex->create();
        m_bedIndex->bind();
        m_bedIndex->setUsagePattern(QOpenGLBuffer::StaticDraw);

        m_program->enableAttributeArray(0);
        m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());

        m_program->enableAttributeArray(1);
        m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::normalOffset(), Vertex::NormalTupleSize, Vertex::stride());

        m_program->enableAttributeArray(2);
        m_program->setAttributeBuffer(2, GL_INT, 0, 3, sizeof(int));

        m_program->enableAttributeArray(3);
        m_program->setAttributeBuffer(3, GL_FLOAT, 0, 2);

        m_bedVertex.release();
        m_bedIndex->release();
        m_bedVAO.release();

        m_surfaceVAO.create();
        m_surfaceVAO.bind();

        m_surfaceVertex.create();
        m_surfaceVertex.bind();
        m_surfaceVertex.setUsagePattern(QOpenGLBuffer::StaticDraw);

        m_surfaceIndex->create();
        m_surfaceIndex->bind();
        m_surfaceIndex->setUsagePattern(QOpenGLBuffer::StaticDraw);

        m_program->enableAttributeArray(0);
        m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());

        m_program->enableAttributeArray(1);
        m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::normalOffset(), Vertex::NormalTupleSize, Vertex::stride());

        m_program->enableAttributeArray(2);
        m_program->setAttributeBuffer(2, GL_INT, 0, 3, sizeof(int));

        m_program->enableAttributeArray(3);
        m_program->setAttributeBuffer(3, GL_FLOAT, 0, 2);

        m_surfaceVertex.release();
        m_surfaceIndex->release();
        m_surfaceVAO.release();

        m_icemaskVAO.create();
        m_icemaskVAO.bind();

        m_icemaskVertex.create();
        m_icemaskVertex.bind();
        m_icemaskVertex.setUsagePattern(QOpenGLBuffer::StaticDraw);

        m_icemaskIndex->create();
        m_icemaskIndex->bind();
        m_icemaskIndex->setUsagePattern(QOpenGLBuffer::StaticDraw);

        m_program->enableAttributeArray(0);
        m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());

        m_program->enableAttributeArray(1);
        m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::normalOffset(), Vertex::NormalTupleSize, Vertex::stride());

        m_program->enableAttributeArray(2);
        m_program->setAttributeBuffer(2, GL_INT, 0, 3, sizeof(int));

        m_program->enableAttributeArray(3);
        m_program->setAttributeBuffer(3, GL_FLOAT, 0, 2);

        m_icemaskVertex.release();
        m_icemaskIndex->release();
        m_icemaskVAO.release();

        m_rockmaskVAO.create();
        m_rockmaskVAO.bind();

        m_rockmaskVertex.create();
        m_rockmaskVertex.bind();
        m_rockmaskVertex.setUsagePattern(QOpenGLBuffer::StaticDraw);

        m_rockmaskIndex->create();
        m_rockmaskIndex->bind();
        m_rockmaskIndex->setUsagePattern(QOpenGLBuffer::StaticDraw);

        m_program->enableAttributeArray(0);
        m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());

        m_program->enableAttributeArray(1);
        m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::normalOffset(), Vertex::NormalTupleSize, Vertex::stride());

        m_program->enableAttributeArray(2);
        m_program->setAttributeBuffer(2, GL_INT, 0, 3, sizeof(int));

        m_program->enableAttributeArray(3);
        m_program->setAttributeBuffer(3, GL_FLOAT, 0, 2);

        m_rockmaskVertex.release();
        m_rockmaskIndex->release();
        m_rockmaskVAO.release();

        m_program->release();

    }
    initializeVertices();  
    loadBuffers();

}

void Canvas::resizeGL(int width, int height)
{
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, width / float(height), 0.1f, 100000.0f);
}

void Canvas::paintGL()
{

    QColor bgColour = GetBgColour();
    glClearColor(bgColour.redF(),bgColour.greenF(),bgColour.blueF(),bgColour.alphaF());
    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render using our shader

    m_program->bind();
    m_program->setUniformValue(u_worldToCamera, m_camera.toMatrix());
    m_program->setUniformValue(u_cameraToView, m_projection);
    {
        m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());


        m_iceVAO.bind();
        if(GetIceSurfaceToggled())
        {
            drawFigure(0);
         }
        m_iceVAO.release();

        m_bedVAO.bind();
        if(GetBedSurfaceToggled())
        {
            drawFigure(1);
         }
        m_bedVAO.release();

        m_surfaceVAO.bind();
        if(GetSurfaceSurfaceToggled())
        {
            drawFigure(2);
         }
        m_surfaceVAO.release();

        m_icemaskVAO.bind();
        if(GetIcemaskSurfaceToggled())
        {
            drawFigure(3);
         }
        m_icemaskVAO.release();

        m_rockmaskVAO.bind();
        if(GetRockmaskSurfaceToggled())
        {
            drawFigure(4);
         }
        m_rockmaskVAO.release();

    }
    m_program->release();
}

void Canvas::update()
{
    // Update input
    UserInput::update();

    float dx = UserInput::mousePosition().x() - m_LastX;
    float dy = UserInput::mousePosition().y() - m_LastY;

    // Camera Transformation
    if (UserInput::buttonPressed(Qt::RightButton))
    {
        static const float transSpeed = 5;
        static const float rotSpeed   = 0.5f;
        static const float zoomSpeed = calculateZoomSpeed(GetResOption());

        // Handle rotations
//        m_camera.rotate(-rotSpeed * UserInput::mouseDelta().x(), Camera3D::LocalUp);
//        m_camera.rotate(-rotSpeed * UserInput::mouseDelta().y(), m_camera.right());

        m_camera.translate(transSpeed*UserInput::mouseDelta().x(), transSpeed*-UserInput::mouseDelta().y(), 0);

        // Handle translations
        QVector3D translation;
        if (UserInput::keyPressed(Qt::Key_Up))
        {
            translation += m_camera.forward()*zoomSpeed;
        }
        if (UserInput::keyPressed(Qt::Key_Down))
        {
            translation -= m_camera.forward()*zoomSpeed;
        }
//        if (UserInput::keyPressed(Qt::Key_Left))
//        {
//            translation -= m_camera.right()*zoomSpeed;
//        }
//        if (UserInput::keyPressed(Qt::Key_Right))
//        {
//            translation += m_camera.right()*zoomSpeed;
//        }
        if (UserInput::keyPressed(Qt::Key_Left))
        {
            float centerX = this->width()/2;
            float centerY = this->height()/2;

            float amount = 2*zoomSpeed ;
            QQuaternion axisRot = QQuaternion::fromAxisAndAngle(m_camera.forward(),
                                                                rotSpeed*
                                                                1*
                                                                amount);
            m_camera.rotate(axisRot);
        }
        if (UserInput::keyPressed(Qt::Key_Right))
        {
            float centerX = this->width()/2;
            float centerY = this->height()/2;

            float amount = 2*zoomSpeed ;
            QQuaternion axisRot = QQuaternion::fromAxisAndAngle(m_camera.forward(),
                                                                rotSpeed*
                                                                -1*
                                                                amount);
            m_camera.rotate(axisRot);
        }
        m_camera.translate(transSpeed * translation);
    }
    // Update instance information

    if (UserInput::buttonPressed(Qt::LeftButton))
    {
        static const float rotSpeed   = 1.0f;

        float centerX = this->width()/2;
        float centerY = this->height()/2;
        bool isLeft = ((m_LastX - centerX)*(UserInput::mousePosition().y() - centerY)
                       - (m_LastY - centerY)*(UserInput::mousePosition().x() - centerX)) > 0;
        int direction = 1;
        if (!isLeft)
        {
            direction = -1;
        }
        float amount = qSqrt(dy*dy+dx*dx)/2;
        QQuaternion axisRot = QQuaternion::fromAxisAndAngle(m_camera.forward(),
                                                            rotSpeed*
                                                            direction*
                                                            amount);
        m_camera.rotate(axisRot);

    QQuaternion upRot = QQuaternion::fromAxisAndAngle(QVector3D(1,1,0),
                                                      -rotSpeed*dy);
    QQuaternion rightRot = QQuaternion::fromAxisAndAngle(QVector3D(1,1,0),
                                                         rotSpeed*dx);

    m_transform.rotate(upRot);
    m_transform.rotate(rightRot);

    }

    if (UserInput::buttonPressed(Qt::MiddleButton))
    {
        resetZoom();
        resetRotation();
        resetTransform();
        resetScale();
        resetTranslation();
    }
//todo
    if(UserInput::keyPressed(Qt::Key_PageUp))
    {
        m_lightPosition.setX(UserInput::mouseDelta().x());
        m_lightPosition.setY(UserInput::mouseDelta().y());
    }

    // Schedule a redraw
    QOpenGLWidget::update();

    SetLastX(UserInput::mousePosition().x());
    SetLastY(UserInput::mousePosition().y());
}

void Canvas::wheelEvent(QWheelEvent *event)
{
    QPoint numDeg = event->angleDelta() / 8;
    static const float transSpeed = 6;
    static const float rotSpeed   = 0.5f;
    static const float zoomSpeed = calculateZoomSpeed(GetResOption());
     // Handle translations
    QVector3D translation;
    translation += m_camera.forward()*zoomSpeed * numDeg.y();
    m_camera.translate(translation);
}

void Canvas::tearDownGL()
{
    // Actually destroy our OpenGL information
    m_iceVAO.destroy();
    m_bedVAO.destroy();
    m_surfaceVAO.destroy();
    m_icemaskVAO.destroy();
    m_rockmaskVAO.destroy();

    m_iceVertex.destroy();
    m_iceIndex->destroy();
    m_bedVertex.destroy();
    m_bedIndex->destroy();
    m_surfaceVertex.destroy();
    m_surfaceIndex->destroy();
    m_icemaskVertex.destroy();
    m_icemaskIndex->destroy();
    m_rockmaskVertex.destroy();
    m_rockmaskIndex->destroy();

    delete m_program;
}

/////////////INITIALIZE///////////
void Canvas::initializeVertices()
{

    o_data->SetOption(m_samplingOption);

    std::vector<Vertex> iceVerteces = o_data->ReadVerticesFromBin(GetResOption(), 0);
    std::vector<int> iceIndeces  = o_data->ReadIndecesFromBins(GetResOption(), 0);

    std::vector<Vertex> bedVerteces = o_data->ReadVerticesFromBin(GetResOption(), 1);
    std::vector<int> bedIndeces  = o_data->ReadIndecesFromBins(GetResOption(), 1);

    std::vector<Vertex> surfaceVerteces = o_data->ReadVerticesFromBin(GetResOption(), 2);
    std::vector<int> surfaceIndeces  = o_data->ReadIndecesFromBins(GetResOption(), 2);

    std::vector<Vertex> icemaskVerteces = o_data->ReadVerticesFromBin(GetResOption(), 3);
    std::vector<int> icemaskIndeces  = o_data->ReadIndecesFromBins(GetResOption(), 3);

    std::vector<Vertex> rockmaskVerteces = o_data->ReadVerticesFromBin(GetResOption(), 4);
    std::vector<int> rockmaskIndeces  = o_data->ReadIndecesFromBins(GetResOption(), 4);

    SetIceIndeces(iceIndeces);
    SetIceVerteces(iceVerteces);

    SetBedIndeces(bedIndeces);
    SetBedVerteces(bedVerteces);

    SetSurfaceIndeces(surfaceIndeces);
    SetSurfaceVerteces(surfaceVerteces);

    SetIcemaskIndeces(icemaskIndeces);
    SetIcemaskVerteces(icemaskVerteces);

    SetRockmaskIndeces(rockmaskIndeces);
    SetRockmaskVerteces(rockmaskVerteces);

    QLocale l = QLocale::system();
    int iceI = iceIndeces.size()/3;
    QString iceS = l.toString(iceI);
    int bedI = bedIndeces.size()/3;
    QString bedS = l.toString(bedI);
    int surI = surfaceIndeces.size()/3;
    QString surS = l.toString(surI);
    int icemaskI = icemaskIndeces.size()/3;
    QString icemaskS = l.toString(icemaskI);
    int rockmaskI = rockmaskIndeces.size()/3;
    QString rockmaskS = l.toString(rockmaskI);

    updateTrianglesLabel("Triangles Rendered: " + iceS ,0);
    updateTrianglesLabel("Triangles Rendered: " + bedS ,1);
    updateTrianglesLabel("Triangles Rendered: " + surS, 2);
    updateTrianglesLabel("Triangles Rendered: " + icemaskS, 3);
    updateTrianglesLabel("Triangles Rendered: " + rockmaskS, 3);

}

void Canvas::loadBuffers()
{
    std::vector<Vertex> iceVerteces = GetIceVerteces();
    std::vector<int> iceIndeces = GetIceIndeces();
    std::vector<Vertex> bedVerteces = GetBedVerteces();
    std::vector<int> bedIndeces = GetBedIndeces();
    std::vector<Vertex> surfaceVerteces = GetSurfaceVerteces();
    std::vector<int> surfaceIndeces = GetSurfaceIndeces(); 
    std::vector<Vertex> icemaskVerteces = GetIcemaskVerteces();
    std::vector<int> icemaskIndeces = GetIcemaskIndeces();
    std::vector<Vertex> rockmaskVerteces = GetRockmaskVerteces();
    std::vector<int> rockmaskIndeces = GetRockmaskIndeces();

    m_iceVertex.bind();
    m_iceVertex.allocate(iceVerteces.data(), iceVerteces.size() * sizeof(Vertex) );
    m_iceVertex.release();

    m_iceIndex->bind();
    m_iceIndex->allocate(iceIndeces.data(), iceIndeces.size() * sizeof(int));
    m_iceIndex->release();

    m_bedVertex.bind();
    m_bedVertex.allocate(bedVerteces.data(), bedVerteces.size() * sizeof(Vertex) );
    m_bedVertex.release();

    m_bedIndex->bind();
    m_bedIndex->allocate(bedIndeces.data(), bedIndeces.size() * sizeof(int));
    m_bedIndex->release();

    m_surfaceVertex.bind();
    m_surfaceVertex.allocate(surfaceVerteces.data(), surfaceVerteces.size() * sizeof(Vertex) );
    m_surfaceVertex.release();

    m_surfaceIndex->bind();
    m_surfaceIndex->allocate(surfaceIndeces.data(), surfaceIndeces.size() * sizeof(int));
    m_surfaceIndex->release();

    m_icemaskVertex.bind();
    m_icemaskVertex.allocate(icemaskVerteces.data(), icemaskVerteces.size() * sizeof(Vertex) );
    m_icemaskVertex.release();

    m_icemaskIndex->bind();
    m_icemaskIndex->allocate(icemaskIndeces.data(), icemaskIndeces.size() * sizeof(int));
    m_icemaskIndex->release();

    m_rockmaskVertex.bind();
    m_rockmaskVertex.allocate(rockmaskVerteces.data(), rockmaskVerteces.size() * sizeof(Vertex) );
    m_rockmaskVertex.release();

    m_rockmaskIndex->bind();
    m_rockmaskIndex->allocate(rockmaskIndeces.data(), rockmaskIndeces.size() * sizeof(int));
    m_rockmaskIndex->release();
}

/////////////DRAW/////////////////

void Canvas::drawFigure(int option)
{
    int size;

    GLint point = GetPointSizeOption();
    int pointSize = m_program->uniformLocation("pointSize");
    m_program->setUniformValue(pointSize, point);

    GLint zFactor = GetZFactorOption() * calculateZoomSpeed(GetResOption());
    int zFactorValue = m_program->uniformLocation("zFactorValue");
    m_program->setUniformValue(zFactorValue, zFactor);

    GLint iceThicknessMapSel = m_iceThicknessMapSelection;
    int iceThicknessMapSelValue = m_program->uniformLocation("iceThicknessMapSelValue");
    m_program->setUniformValue(iceThicknessMapSelValue, iceThicknessMapSel);

    GLint bedMapSel = m_bedMapSelection;
    int bedMapSelValue = m_program->uniformLocation("bedMapSelValue");
    m_program->setUniformValue(bedMapSelValue, bedMapSel);

    int lightPositionValue = m_program->uniformLocation("lightPositionValue");
    m_program->setUniformValue(lightPositionValue, m_lightPosition.x(), m_lightPosition.y(), m_lightPosition.z());

    int lightColourValue = m_program->uniformLocation("lightColourValue");
    m_program->setUniformValue(lightColourValue, m_lightColour.x(), m_lightColour.y(), m_lightColour.z());

    GLint lightingSel = m_lightingSelection;
    int lightingSelValue = m_program->uniformLocation("lightingSelValue");
    m_program->setUniformValue(lightingSelValue, lightingSel);

    GLint zOffset = 1;

    GLint surface = 1;

    switch (option) {
    case 0:
       size = m_iceIndeces.size();
        m_iceIndex->bind();
        zOffset = GetZOffsetOption() * calculateZoomSpeed(GetResOption());
        surface = 0;
        break;
    case 1:
        size = m_bedIndeces.size();
        m_bedIndex->bind();
        surface = 1;
        break;
    case 2:
        size = m_surfaceIndeces.size();
        m_surfaceIndex->bind();
        surface = 2;
        break;     
    case 3:
        size = m_icemaskIndeces.size();
        m_icemaskIndex->bind();
        surface = 3;
        break;
    case 4:
        size = m_rockmaskIndeces.size();
        m_rockmaskIndex->bind();
        surface = 4;
        break;
    }

    int zOffsetValue = m_program->uniformLocation("zOffsetValue");
    m_program->setUniformValue(zOffsetValue, zOffset);

    int surfaceValue = m_program->uniformLocation("surfaceValue");
    m_program->setUniformValue(surfaceValue, surface);

    switch (GetDrawOption())
    {
    case 0:
        glDrawElements(GL_POINTS, size, GL_UNSIGNED_INT, Q_NULLPTR);
        break;
    case 1:
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, Q_NULLPTR);
        break;
    case 2:
        glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_INT, Q_NULLPTR);
        break;
    }

    switch (option) {
    case 0:
        m_iceIndex->release();
        break;
    case 1:
        m_bedIndex->release();
        break;
    case 2:
        m_surfaceIndex->release();
        break;
    case 3:
        m_icemaskIndex->release();
        break;
    case 4:
        m_rockmaskIndex->release();
        break;
    }

}

void Canvas::resetRotation()
{
    m_camera.ResetView(GetResOption()/2,GetResOption()/2, m_camera.translation().z());
}

void Canvas::resetTransform()
{
        m_transform.ResetTransform();
}

void Canvas::resetZoom()
{
    m_camera.ResetView(m_camera.translation().x(),m_camera.translation().y(), GetResOption()*1.5);
}

void Canvas::resetScale()
{
    SetZFactorOption(Constants::SCALE_DEFAULT);
    emit Si_SetZFactorOption(Constants::SCALE_DEFAULT);
}

void Canvas::resetTranslation()
{
    SetZOffsetOption(Constants::TRANSLATION_DEFAULT);
    emit Si_SetZOffsetOption(Constants::TRANSLATION_DEFAULT);
}


/////////////EVENTS/////////////////

void Canvas::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        event->ignore();
    }
    else
    {
        UserInput::registerKeyPress(event->key());
    }
}

void Canvas::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        event->ignore();
    }
    else
    {
        UserInput::registerKeyRelease(event->key());
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    UserInput::registerMousePress(event->button());
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    UserInput::registerMouseRelease(event->button());
}

/////////////SIGNALS////////////////
void Canvas::updateProgressBar(int value, QString label)
{
    SetProgressValue(value);
    SetProgressStatus(label);
    emit Si_SetProgressBarLabel(GetProgressStatus());
    emit Si_SetProgressBarValue(GetProgressValue());

}

void Canvas::updateTrianglesLabel(QString label, int option)
{
    switch(option)
    {
    case 0:
        emit Si_SetIceTrianglesLabel(label);
        break;
    case 1:
        emit Si_SetBedTrianglesLabel(label);
        break;
    case 2:
        emit Si_SetSurfaceTrianglesLabel(label);
        break;
    case 3:
        emit Si_SetIcemaskTrianglesLabel(label);
        break;
    case 4:
        emit Si_SetRockmaskTrianglesLabel(label);
        break;
    }
}

/////////////SLOTS/////////////////
void Canvas::S_GetDrawOption(int option)
{
    SetDrawOption(option);
}

void Canvas::S_GetResOption(int option)
{
    int res;

    if(m_samplingOption == 0)
    {
        switch(option)
        {
        case 0:
            res = 52;
            break;
        case 1:
            res = 103;
            break;
        case 2:
            res = 203;
            break;
        case 3:
            res = 393;
            break;
        case 4:
            res = 741;
            break;
        case 5:
            res = 1334;
            break;
        case 6:
            res = 2223;
            break;
        case 7:
            res = 3334;
            break;
        case 8:
            res = 6667;
            break;
        }
    }else {
        switch(option)
        {
        case 0:
            res = 52;
            break;
        case 1:
            res = 104;
            break;
        case 2:
            res = 208;
            break;
        case 3:
            res = 416;
            break;
        case 4:
            res = 833;
            break;
        case 5:
            res = 1666;
            break;
        case 6:
            res = 2223;
            break;
        case 7:
            res = 3333;
            break;
        }
    }

    SetResOption(res);
    initializeVertices();
    loadBuffers();
    float z = m_camera.translation().z();
    m_camera.ResetView(res/2,res/2, z);
    SetZFactorOption(1);
    SetZOffsetOption(1);
    //m_transform.ResetTransform();
    update();
}

void Canvas::S_GetBgOption(int option)
{
    QColor bgColour;

    switch(option)
    {
    case 0:
        bgColour = Qt::gray;
        break;
    case 1:
        bgColour = Qt::blue;
        break;
    case 2:
        bgColour = Qt::green;
        break;
    case 3:
        bgColour = Qt::black;
        break;
    case 4:
        bgColour = Qt::white;
        break;
    }

    SetBgColour(bgColour);
    update();
}

void Canvas::S_GetPointSizeOption(int option)
{
    SetPointSizeOption(option);
}

void Canvas::S_GetZFactorOption(int option)
{
    SetZFactorOption(option);
}

void Canvas::S_GetZOffsetOption(int option)
{
    SetZOffsetOption(option);
}

void Canvas::S_GetIceSurfaceToggle(bool toggle)
{
    SetIceSurfaceToggled(toggle);
}

void Canvas::S_GetBedSurfaceToggle(bool toggle)
{
    SetBedSurfaceToggled(toggle);
}

void Canvas::S_GetSurfaceSurfaceToggle(bool toggle)
{
    SetSurfaceSurfaceToggled(toggle);
}

void Canvas::S_GetIcemaskSurfaceToggle(bool toggle)
{
    SetIcemaskSurfaceToggled(toggle);
}

void Canvas::S_GetRockmaskSurfaceToggle(bool toggle)
{
    SetRockmaskSurfaceToggled(toggle);
}

void Canvas::S_GetMenuResetRotAction()
{
    resetRotation();
}

void Canvas::S_GetMenuResetZoomAction()
{
    resetZoom();
}

void Canvas::S_GetMenuResetTransformAction()
{
    resetTransform();
}

void Canvas::S_GetSamplingOption()
{
    int option;
    if(m_samplingOption == 0)
    {
        option = 1;
    }else {
        option = 0;
    }
    SetSamplingOption(option);
}

void Canvas::S_GetMenuResetScaleAction()
{
    resetScale();
}

void Canvas::S_GetMenuResetTranAction()
{
    resetTranslation();
}

void Canvas::S_GetIceThicknessMap(int map)
{
    m_iceThicknessMapSelection = map;
}

void Canvas::S_GetBedMap(int map)
{
    m_bedMapSelection = map;
}

void Canvas::S_GetLightingSelection(int sel)
{
    m_lightingSelection = sel;
}
void Canvas::S_GetLightingColourRed(int red)
{
    m_lightColour.setX(red/10);
}
void Canvas::S_GetLightingColourGreen(int green)
{
    m_lightColour.setY(green/10);
}
void Canvas::S_GetLightingColourBlue(int blue)
{
    m_lightColour.setZ(blue/10);
}

//FILTHY DUPLICATE FUNCTION FROM DATA HANDLER


int Canvas::calculateZoomSpeed(int dimension)
{
    int speed;
    if(m_samplingOption == 0)
    {
        switch (dimension)
        {
        case 52:
            speed = 1;
            break;
        case 103:
            speed = 2;
            break;
        case 203:
            speed = 4;
            break;
        case 393:
            speed = 8;
            break;
        case 741:
            speed = 16;
            break;
        case 1334:
            speed = 32;
            break;
        case 2223:
            speed = 2*64;
            break;
        case 3334:
            speed = 4*128;
            break;
        case 6667:
            speed = 8*256;
            break;
        }
    }else {
        switch(dimension)
        {
        case 52:
            speed = 52;
            break;
        case 104:
            speed = 2;
            break;
        case 208:
            speed = 4;
            break;
        case 416:
            speed = 8;
            break;
        case 833:
            speed = 16;
            break;
        case 1666:
            speed = 32;
            break;
        case 2223:
            speed = 64;
            break;
        case 3333:
            speed = 128;
            break;
        }
    }

    return speed;
}


/////////////ACCESSORS/////////////////

QColor Canvas::GetBgColour()
{
    return m_bgColour;
}

void Canvas::SetBgColour(QColor bgColour)
{
    m_bgColour = bgColour;
}

void Canvas::SetDrawOption(int option)
{
    m_drawOption = option;
}

int Canvas::GetDrawOption()
{
    return m_drawOption;
}

void Canvas::SetResOption(int option)
{
    m_resOption = option;
}

int Canvas::GetResOption()
{
    return m_resOption;
}

void Canvas::SetPointSizeOption(int option)
{
    m_pointSizeOption = option;
}

int Canvas::GetPointSizeOption()
{
    return m_pointSizeOption;
}

void Canvas::SetZFactorOption(int option)
{
    m_zFactorOption = option;
}

int Canvas::GetZFactorOption()
{
    return m_zFactorOption;
}

void Canvas::SetZOffsetOption(int option)
{
    m_zOffsetOption = option;
}

int Canvas::GetZOffsetOption()
{
    return m_zOffsetOption;
}

std::vector<int> Canvas::GetIceIndeces()
{
    return m_iceIndeces;
}


void Canvas::SetIceIndeces(std::vector<int> iceIndeces)
{
    m_iceIndeces = iceIndeces;
}

std::vector<Vertex> Canvas::GetIceVerteces()
{
    return m_iceVerteces;
}

void Canvas::SetIceVerteces(std::vector<Vertex> iceVerteces)
{
    m_iceVerteces = iceVerteces;
}

std::vector<int> Canvas::GetBedIndeces()
{
    return m_bedIndeces;
}


void Canvas::SetBedIndeces(std::vector<int> bedIndeces)
{
    m_bedIndeces = bedIndeces;
}

std::vector<Vertex> Canvas::GetBedVerteces()
{
    return m_bedVerteces;
}

void Canvas::SetBedVerteces(std::vector<Vertex> bedVerteces)
{
    m_bedVerteces = bedVerteces;
}

std::vector<int> Canvas::GetSurfaceIndeces()
{
    return m_surfaceIndeces;
}


void Canvas::SetSurfaceIndeces(std::vector<int> surfaceIndeces)
{
    m_surfaceIndeces = surfaceIndeces;
}

std::vector<Vertex> Canvas::GetSurfaceVerteces()
{
    return m_surfaceVerteces;
}

void Canvas::SetSurfaceVerteces(std::vector<Vertex> surfaceVerteces)
{
    m_surfaceVerteces = surfaceVerteces;
}

std::vector<int> Canvas::GetIcemaskIndeces()
{
    return m_icemaskIndeces;
}


void Canvas::SetIcemaskIndeces(std::vector<int> icemaskIndeces)
{
    m_icemaskIndeces = icemaskIndeces;
}

std::vector<Vertex> Canvas::GetIcemaskVerteces()
{
    return m_icemaskVerteces;
}

void Canvas::SetIcemaskVerteces(std::vector<Vertex> icemaskVerteces)
{
    m_icemaskVerteces = icemaskVerteces;
}

std::vector<int> Canvas::GetRockmaskIndeces()
{
    return m_rockmaskIndeces;
}


void Canvas::SetRockmaskIndeces(std::vector<int> rockmaskIndeces)
{
    m_rockmaskIndeces = rockmaskIndeces;
}

std::vector<Vertex> Canvas::GetRockmaskVerteces()
{
    return m_rockmaskVerteces;
}

void Canvas::SetRockmaskVerteces(std::vector<Vertex> rockmaskVerteces)
{
    m_rockmaskVerteces = rockmaskVerteces;
}

QString Canvas::GetProgressStatus()
{
    return m_progressStatus;
}

void Canvas::SetProgressStatus(QString progressStatus)
{
    m_progressStatus = progressStatus;
}

int Canvas::GetProgressValue()
{
    return m_progressValue;
}

void Canvas::SetProgressValue(int progressValue)
{
    m_progressValue = progressValue;
}

void Canvas::SetLastX(float LastX)
{
    m_LastX = LastX;
}

void Canvas::SetLastY(float LastY)
{
    m_LastY = LastY;
}

bool Canvas::GetSurfaceSurfaceToggled() const
{
    return m_surfaceSurfaceToggled;
}

void Canvas::SetSurfaceSurfaceToggled(bool surfaceSurfaceToggled)
{
    m_surfaceSurfaceToggled = surfaceSurfaceToggled;
}

bool Canvas::GetBedSurfaceToggled() const
{
    return m_bedSurfaceToggled;
}

void Canvas::SetBedSurfaceToggled(bool bedSurfaceToggled)
{
    m_bedSurfaceToggled = bedSurfaceToggled;
}

bool Canvas::GetIceSurfaceToggled() const
{
    return m_iceSurfaceToggled;
}

void Canvas::SetIceSurfaceToggled(bool iceSurfaceToggled)
{
    m_iceSurfaceToggled = iceSurfaceToggled;
}

bool Canvas::GetIcemaskSurfaceToggled() const
{
    return m_icemaskSurfaceToggled;
}

void Canvas::SetIcemaskSurfaceToggled(bool icemaskSurfaceToggled)
{
    m_icemaskSurfaceToggled = icemaskSurfaceToggled;
}

bool Canvas::GetRockmaskSurfaceToggled() const
{
    return m_rockmaskSurfaceToggled;
}

void Canvas::SetRockmaskSurfaceToggled(bool rockmaskSurfaceToggled)
{
    m_rockmaskSurfaceToggled = rockmaskSurfaceToggled;
}

int Canvas::GetSamplingOption()
{
    return m_samplingOption;
}

void Canvas::SetSamplingOption(int option)
{
     m_samplingOption = option;
}

