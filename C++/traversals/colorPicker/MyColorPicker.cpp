#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(HSLAPixel pix0, HSLAPixel pix1, unsigned interval)
  : p0(pix0),
    p1(pix1),
    interval_(interval)
{

}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  unsigned val = x % interval_;
  if (val < interval_/2){
    return p0;
  } else {
    return p1;
  }
}
