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



const float Constants::MIN_THICKNESS = -1;
const float Constants::MAX_THICKNESS = 4.621;
GeometryProcessor *setUp;

DataHandler *o_data = new DataHandler();
ColourMap *o_cMap = &o_cMap->GetColourMapObject();

Canvas::Canvas(QWidget *parent) : QOpenGLWidget(parent)
{
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    m_transform.translate(-50.0f, -50.0f, -100.0f);
    m_drawOption = 0;
    m_resOption = 52;
    m_pointSizeOption = 5;
    setUp = new GeometryProcessor();
    SetBgColour(Qt::black);

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

        // Create Buffer (Do not release until VAO is created)
        m_triVertex.create();
        m_triVertex.bind();
        m_triVertex.setUsagePattern(QOpenGLBuffer::StaticDraw);

        m_triIndex->create();
        m_triIndex->bind();
        m_triIndex->setUsagePattern(QOpenGLBuffer::StaticDraw);

        // Create Vertex Array Object (VAO)
        m_triangleVAO.create();
        m_triangleVAO.bind();

//        m_program->enableAttributeArray(0);
//        m_program->enableAttributeArray(1);
//        m_program->enableAttributeArray(2);
//        m_program->enableAttributeArray(3);

//        m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
//        m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());
//        m_program->setAttributeBuffer(2, GL_FLOAT, 0, 1);
//        m_program->setAttributeBuffer(3, GL_FLOAT, 0, 1, sizeof(int));


        // Release (unbind) all
        m_triangleVAO.release();
        m_triVertex.release();
        m_triIndex->release();
        m_program->release();


        }
   initializeVertices();
}

void Canvas::resizeGL(int width, int height)
{
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
}

void Canvas::paintGL()
{

    QColor bgColour = GetBgColour();
    glClearColor(bgColour.redF(),bgColour.greenF(),bgColour.blueF(),bgColour.alphaF());
    // Clear
    glClear(GL_COLOR_BUFFER_BIT);
    // Render using our shader

    m_program->bind();
    m_program->setUniformValue(u_worldToCamera, m_camera.toMatrix());
    m_program->setUniformValue(u_cameraToView, m_projection);
    {
        m_triangleVAO.bind();
        m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());

        drawFigure();

        m_triangleVAO.release();

    }
    m_program->release();
}

void Canvas::update()
{
    // Update input
    UserInput::update();

    // Camera Transformation
    if (UserInput::buttonPressed(Qt::RightButton))
    {
        static const float transSpeed = 5.0f;
        static const float rotSpeed   = 0.5f;

        // Handle rotations
        m_camera.rotate(-rotSpeed * UserInput::mouseDelta().x(), Camera3D::LocalUp);
        m_camera.rotate(-rotSpeed * UserInput::mouseDelta().y(), m_camera.right());

        // Handle translations
        QVector3D translation;
        if (UserInput::keyPressed(Qt::Key_Up))
        {
            translation += m_camera.forward();
        }
        if (UserInput::keyPressed(Qt::Key_Down))
        {
            translation -= m_camera.forward();
        }
        if (UserInput::keyPressed(Qt::Key_Left))
        {
            translation -= m_camera.right();
        }
        if (UserInput::keyPressed(Qt::Key_Right))
        {
            translation += m_camera.right();
        }
        if (UserInput::keyPressed(Qt::Key_Q))
        {
            translation -= m_camera.up();
        }
        if (UserInput::keyPressed(Qt::Key_E))
        {
            translation += m_camera.up();
        }
        m_camera.translate(transSpeed * translation);
    }
    // Update instance information
    //m_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));
    if (UserInput::buttonPressed(Qt::LeftButton))
    {
        static const float transSpeed = 0.5f;
        static const float rotSpeed   = 1.0f;
        m_transform.rotate(-rotSpeed * -UserInput::mouseDelta().x(), Camera3D::LocalUp);
        m_transform.rotate(-rotSpeed * -UserInput::mouseDelta().y(), m_camera.right());

    }

    // Schedule a redraw
    QOpenGLWidget::update();
}


void Canvas::tearDownGL()
{
    // Actually destroy our OpenGL information
    m_triangleVAO.destroy();
    m_triVertex.destroy();
    m_triIndex->destroy();
    delete m_program;
}

/////////////INITIALIZE///////////
void Canvas::initializeVertices()
{
    updateProgressBar(10, "initializing");

    std::vector<Vertex> triVerteces; // = o_data->ReadVerticesFromBin(GetResOption());
    std::vector<int> triIndeces; // = o_data->ReadIndecesFromBins(GetResOption());

    QElapsedTimer timer;
    timer.start();

    updateProgressBar(20, "getting data");

//    setUp->GenerateQuads(GetResOption());


//    updateProgressBar(30, "generating triangles");
//    setUp->GenerateTriangles();

//    updateProgressBar(40, "setting up vertices");
//    setUp->SetUpVertices();

//    updateProgressBar(60, "assigning colours");



    setUp->CreateTriangles(GetResOption());

     qDebug() << "The dirty func took" << timer.elapsed() << "milliseconds";

    QList<QVector3D> list = setUp->GetVertList();
    for(auto l : list)
    {
        int index =  o_data->Normalize(0, Constants::MAX_THICKNESS, 0, 9, l.z());

        QColor colour = o_cMap->GetColourFromMap(9-index);
        QVector3D *col = new QVector3D(colour.redF(), colour.greenF(), colour.blueF());
        triVerteces.push_back(Vertex(l, *col));
    }

    triIndeces = setUp->GetTriIndeces();

    SetTriIndeces(triIndeces);
    SetTriVerteces(triVerteces);

//    updateProgressBar(80, "preparing canvas");
//    //updateProgressBar(85, "done");
//    updateProgressBar(90, "preparing VAO");
//    //updateProgressBar(95, "drawing");
//    updateProgressBar(100, "Running...");
    updateTrianglesLabel("Triangles Rendered: " + QString::number(triIndeces.size()/3));

//    o_data->WriteIndecesToBins(GetResOption(),triIndeces);
//    o_data->WriteVerticesToBin(GetResOption(), triVerteces);
}

/////////////DRAW/////////////////

void Canvas::drawFigure()
{

    std::vector<Vertex> triVerteces = GetTriVerteces();
    std::vector<int> triIndeces = GetTriIndeces();



    m_triVertex.bind();
    m_triVertex.allocate(triVerteces.data(), triVerteces.size() * sizeof(Vertex) );
    m_triVertex.release();

    m_triIndex->bind();
    m_triIndex->allocate(triIndeces.data(), triIndeces.size() * sizeof(int));
    m_triIndex->release();

    m_program->bind();

    m_triVertex.bind();
    m_program->enableAttributeArray(0);
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    m_triVertex.release();

    m_triVertex.bind();
    m_program->enableAttributeArray(1);
     m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());
    m_triVertex.release();

    m_triIndex->bind();
    m_program->enableAttributeArray(2);
    m_program->setAttributeBuffer(2, GL_INT, 0, 3, sizeof(int));
    m_triIndex->release();

    m_program->enableAttributeArray(3);
    m_program->setAttributeBuffer(3, GL_FLOAT, 0, 2);

    GLint point = GetPointSizeOption();
    int pointSize = m_program->uniformLocation("pointSize");
    m_program->setUniformValue(pointSize, point);

    switch (GetDrawOption())
    {
        case 0:
            glDrawElements(GL_POINTS, triIndeces.size(), GL_UNSIGNED_INT, triIndeces.data());
            break;
        case 1:
            glDrawElements(GL_TRIANGLES, triIndeces.size(), GL_UNSIGNED_INT, triIndeces.data());
            break;
        case 2:
            glDrawElements(GL_TRIANGLE_STRIP, triIndeces.size(), GL_UNSIGNED_INT, triIndeces.data());
            break;
    }

    //updateProgressBar(100, "Running...");
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, triVerteces.size() * Vertex::stride());

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

QPointF Canvas::normaliseMouseCoord(QPoint p)
{
    double maxRY = this->height();
    double maxRX = this->width();
    double minRX = 0;
    double minRY = 0;
    double minTX = 0;
    double minTY = 0;
    double maxTX = 100;
    double maxTY = 100;

    double mx = ((p.x() - minRX)/(maxRX - minRX))*(maxTX-minTX)+minTX;
    double my = (((p.y() - minRY)/(maxRY - minRY))*(maxTY-minTY)+minTY);

    return QPointF(mx,my);

}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos = normaliseMouseCoord(event->pos());
    QToolTip::showText(event->screenPos().toPoint(), QString::number(pos.x()) + " , " + QString::number(pos.y()), this);

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

std::vector<int> Canvas::GetTriIndeces()
{
    return m_triIndeces;
}


void Canvas::SetTriIndeces(std::vector<int> triIndeces)
{
    m_triIndeces = triIndeces;
}

std::vector<Vertex> Canvas::GetTriVerteces()
{
    return m_triVerteces;
}

void Canvas::SetTriVerteces(std::vector<Vertex> triVerteces)
{
    m_triVerteces = triVerteces;
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


/////////////SIGNALS////////////////
void Canvas::updateProgressBar(int value, QString label)
{
    SetProgressValue(value);
    SetProgressStatus(label);
    emit Si_SetProgressBarLabel(GetProgressStatus());
    emit Si_SetProgressBarValue(GetProgressValue());

}

void Canvas::updateTrianglesLabel(QString label)
{
    emit Si_SetTrianglesLabel(label);
}

/////////////SLOTS/////////////////
void Canvas::S_GetDrawOption(int option)
{
    SetDrawOption(option);
}

void Canvas::S_GetResOption(int option)
{
    int res;

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
    SetResOption(res);
    initializeVertices();
    update();
}

void Canvas::S_GetBgOption(int option)
{
    QColor bgColour;

    switch(option)
    {
        case 0:
            bgColour = Qt::black;
            break;
        case 1:
            bgColour = Qt::blue;
            break;
        case 2:
            bgColour = Qt::green;
            break;
        case 3:
            bgColour = Qt::gray;
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


