/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include "cs225/PNG.h"

using namespace cs225;

class Image : public PNG
{
  public:
    // ctor, dtor, and assignment operator.
    //Image(unsigned x, unsigned y);
    //Image();
//    ~Image();
    //Image & operator=(const Image & other);

    // member functions
    // ligthen, darken, saturate, desaturate, grayscale, rotate color
    // illinify, scale.
    void lighten();
    void lighten(double amount);
    void darken();
    void darken(double amount);
    void saturate();
    void saturate(double amount);
    void desaturate();
    void desaturate(double amount);
    void grayscale();
    void rotateColor(double degrees);
    void illinify();
    void scale(double factor);
    void scale(unsigned w, unsigned h);

/*
  private:
    void _copy(const Image & other);
    void _clear();
*/

};
