#include "colourmap.h"

QColor ColourMap::GetColourFromMap(int index)
{
    return  ColourMap::COLOUR_MAP[index];
}

QColor ColourMap::GetColourFromBedMap(int index)
{
    return  ColourMap::BED_COLOUR_MAP[index];
}

QColor ColourMap::GetColourFromSurfaceMap(int index)
{
    return  ColourMap::SURFACE_COLOUR_MAP[index];
}

