/**
 * @file camera3D.h
 * @author Carlo Sarli
 * @date 30 August 2019
 * @brief This class provides Camera functionalty for  the canvas.
 *
 * Detailed description goes here.
 */

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
    QColor GetColourFromBedMap(int index);
    QColor GetColourFromSurfaceMap(int index);

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

    const QColor BED_COLOUR_MAP[9] = {
        QColor(255,255,255),
        QColor(240,240,240),
        QColor(217,217,217),
        QColor(189,189,189),
        QColor(150,150,150),
        QColor(115,115,115),
        QColor(82,82,82),
        QColor(37,37,37),
        QColor(0,0,0)
    };

    const QColor SURFACE_COLOUR_MAP[9] = {
        QColor(252,251,253),
        QColor(239,237,245),
        QColor(218,218,235),
        QColor(188,189,220),
        QColor(158,154,200),
        QColor(128,125,186),
        QColor(84,39,143),
        QColor(84,39,143),
        QColor(63,0,125)
    };



};

#endif // COLOURMAP_H
