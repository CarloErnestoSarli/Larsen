#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QColor>


class Constants
{
public:
    Constants();

    static const int SQUARED = 2;
    static const int OCTET = 255;
    static const float MIN_THICKNESS;
    static const float MAX_THICKNESS;
    static const int DIMENSION = 103;

    typedef struct vec {
        float x;
        float y;
        float z;
    }Vector;


private:


};

#endif // CONSTANTS_H
