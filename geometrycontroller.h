//#ifndef GEOMETRYCONTROLLER_H
//#define GEOMETRYCONTROLLER_H

//#include <QObject>
//#include <QThread>
//#include <QElapsedTimer>

//#include "geometryworker.h"
//#include "datahandler.h"

//class GeometryController : public QObject
//{
//    Q_OBJECT
//    QThread worker1;
//    QThread worker2;
//    QThread worker3;
//    QThread worker4;

//public:
//    GeometryController(int dimension);
//    ~GeometryController();

//    void SetPoints(std::vector<std::vector<float>> points);
//    std::vector<std::vector<float>> GetPoints();

//private:
//    DataHandler *o_data;
//    std::vector<std::vector<float>> m_points;

//    void readPoints(int dimension);
//public slots:
//    void handleResults(const QString &);

//signals:
//    void operate(const QString &);
//};

//#endif // GEOMETRYCONTROLLER_H
