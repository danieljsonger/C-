/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    if (theSource.getRows() == 0 || theSource.getColumns() == 0) { return NULL; }
    if (theTiles.size() == 0) { return NULL; }

    std::map<Point<3>, TileImage*> color_map;

    MosaicCanvas *canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    vector<Point<3>> points;

    for (TileImage & tile : theTiles) {
        points.push_back(convertToXYZ(tile.getAverageColor()));
        color_map[convertToXYZ(tile.getAverageColor())] = & tile;
    }

    KDTree<3> tree(points);

    for (int i = 0; i < theSource.getRows(); i++) {
        for (int j = 0; j < theSource.getColumns(); j++) {
            TileImage * image = color_map[tree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i,j)))];
            canvas->setTile(i,j,image);
        }
    }

    return canvas;
}

