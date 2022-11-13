#pragma once

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  MyColorPicker(HSLAPixel pix0, HSLAPixel pix1, unsigned interval);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  HSLAPixel p0;
  HSLAPixel p1;
  unsigned interval_; // making stripes

};
