#ifndef COLOURMAP_H
#define COLOURMAP_H

#include <QColor>



class ColourMap
{
public:

    static ColourMap& GetColourMapObject()
    {
        static ColourMap o_map;
        return o_map;
    }

    ColourMap(ColourMap const&) = delete;
    void operator=(ColourMap const&) = delete;
    QColor GetColourFromMap(int index);

private:

    ColourMap() {}

    const QColor COLOUR_MAP[9] = {
        QColor(247.0f,251.0f,255.0f),
        QColor(222.0f,235.0f,247.0f),
        QColor(198.0f,219.0f,239.0f),
        QColor(158.0f,202.0f,225.0f),
        QColor(107.0f,174.0f,214.0f),
        QColor(66.0f,146.0f,198.0f),
        QColor(33.0f,113.0f,181.0f),
        QColor(8.0f,81.0f,156.0f),
        QColor(8.0f,48.0f,107.0f)
    };



};

#endif // COLOURMAP_H
