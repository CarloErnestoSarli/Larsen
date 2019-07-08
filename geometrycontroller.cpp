//#include "geometrycontroller.h"

//GeometryController::GeometryController(int dimension)
//{
//    o_data = new DataHandler();

//    readPoints(dimension);

//    GeometryWorker *workerA = new GeometryWorker;
//    GeometryWorker *workerB = new GeometryWorker;
//    GeometryWorker *workerC = new GeometryWorker;
//    GeometryWorker *workerD = new GeometryWorker;

//    workerA->moveToThread(&worker1);
//    workerB->moveToThread(&worker2);
//    workerC->moveToThread(&worker3);
//    workerD->moveToThread(&worker4);

//    connect(&worker1, SIGNAL(finished()), workerA, SLOT(deleteLater()));
//    connect(this, SIGNAL(operate(QString)), workerA, SLOT(doWork(QString)));
//    connect(workerA, SIGNAL(resultReady(QString)), this, SLOT(handleResults(QString)));

//    connect(&worker2, SIGNAL(finished()), workerB, SLOT(deleteLater()));
//    connect(this, SIGNAL(operate(QString)), workerB, SLOT(doWork(QString)));
//    connect(workerB, SIGNAL(resultReady(QString)), this, SLOT(handleResults(QString)));

//    connect(&worker3, SIGNAL(finished()), workerC, SLOT(deleteLater()));
//    connect(this, SIGNAL(operate(QString)), workerC, SLOT(doWork(QString)));
//    connect(workerC, SIGNAL(resultReady(QString)), this, SLOT(handleResults(QString)));

//    connect(&worker4, SIGNAL(finished()), workerD, SLOT(deleteLater()));
//    connect(this, SIGNAL(operate(QString)), workerD, SLOT(doWork(QString)));
//    connect(workerD, SIGNAL(resultReady(QString)), this, SLOT(handleResults(QString)));

//    worker1.start();
//    worker2.start();
//    worker3.start();
//    worker4.start();
//}

//GeometryController::~GeometryController() {
//    worker1.quit();
//    worker1.wait();
//    worker2.quit();
//    worker2.wait();
//    worker3.quit();
//    worker3.wait();
//    worker4.quit();
//    worker4.wait();
//}


//void GeometryController::readPoints(int dimension)
//{
//    QElapsedTimer timer;
//    timer.start();

//    SetPoints(o_data->ReadPointsFromBinary(dimension));

//    qDebug() << "The readPoints func took" << timer.elapsed() << "milliseconds";
//}

///////////////////ACCESSORS////////////////

//void GeometryController::SetPoints(std::vector<std::vector<float> > points)
//{
//    m_points = points;
//}

//std::vector<std::vector<float>> GeometryController::GetPoints()
//{
//    return m_points;
//}
