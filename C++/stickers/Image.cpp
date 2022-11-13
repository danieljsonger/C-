#include "Image.h"

using namespace cs225;

/*
Image::Image(unsigned x, unsigned y)
  : PNG(x,y)
  {}

Image::Image()
  : PNG()
  {}
*/
/*
Image::~Image()
{
  // not sure what to do here.
  delete this;
}
*/
/*
Image & Image::operator=(const Image & other)
{
  *this = other;
  return *this;
}
*/

void Image::lighten()
{

  for (unsigned i = 0; i < this->width(); i++){
    for (unsigned j = 0; j < this->height(); j++){

      HSLAPixel & pix = this->getPixel(i,j);

      if (pix.l <=.9){
        pix.l += 0.1;
      } else {
        pix.l = 1.0;
      }

    }
  }

}

void Image::lighten(double amount)
{

  for (unsigned i = 0; i < this->width(); i++){
    for (unsigned j = 0; j < this->height(); j++){

      HSLAPixel & pix = this->getPixel(i,j);

      if (pix.l <=(1 - amount)){
        pix.l += amount;
      } else {
        pix.l = 1.0;
      }

    }
  }

}

void Image::darken()
{

  for (unsigned i = 0; i < this->width(); i++){
    for (unsigned j = 0; j < this->height(); j++){

      HSLAPixel & pix = this->getPixel(i,j);

      if (pix.l >=.1){
        pix.l -= 0.1;
      } else {
        pix.l = 0.0;
      }

    }
  }

}

void Image::darken(double amount)
{

  for (unsigned i = 0; i < this->width(); i++){
    for (unsigned j = 0; j < this->height(); j++){

      HSLAPixel & pix = this->getPixel(i,j);

      if (pix.l >= amount){
        pix.l -= amount;
      } else {
        pix.l = 0.0;
      }

    }
  }

}

void Image::saturate()
{

  for (unsigned i = 0; i < this->width(); i++){
    for (unsigned j = 0; j < this->height(); j++){

      HSLAPixel & pix = this->getPixel(i,j);

      if (pix.s <= 0.9){
        pix.s += 0.1;
      } else {
        pix.s = 1.0;
      }

    }
  }

}

void Image::saturate(double amount)
{

  for (unsigned i = 0; i < this->width(); i++){
    for (unsigned j = 0; j < this->height(); j++){

      HSLAPixel & pix = this->getPixel(i,j);

      if (pix.s <= (1.0 - amount)){
        pix.s += amount;
      } else {
        pix.s = 1.0;
      }

    }
  }

}

void Image::desaturate()
{

  for (unsigned i = 0; i < this->width(); i++){
    for (unsigned j = 0; j < this->height(); j++){

      HSLAPixel & pix = this->getPixel(i,j);

      if (pix.s >= .1){
        pix.s -= 0.1;
      } else {
        pix.s = 0.0;
      }

    }
  }

}

void Image::desaturate(double amount)
{

  for (unsigned i = 0; i < this->width(); i++){
    for (unsigned j = 0; j < this->height(); j++){

      HSLAPixel & pix = this->getPixel(i,j);

      if (pix.s >= amount){
        pix.s -= amount;
      } else {
        pix.s = 0.0;
      }

    }
  }

}

void Image::grayscale()
{

  for (unsigned i = 0; i < this->width(); i++){
    for (unsigned j = 0; j < this->height(); j++){

      HSLAPixel & pix = this->getPixel(i,j);

      pix.s = 0.0;

    }
  }


}

void Image::rotateColor(double degrees)
{

  double tempHue = 0;

  for (unsigned i = 0; i < this->width(); i++){
    for (unsigned j = 0; j < this->height(); j++){

      HSLAPixel & pix = this->getPixel(i,j);

      tempHue = pix.h + degrees;
      if (tempHue > 360 ) {
        tempHue -= 360;
      } else if (tempHue < 0){
        tempHue += 360;
      }

      pix.h = tempHue;

    }
  }

}

void Image::illinify()
{

  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {

      HSLAPixel & pixel = this->getPixel(x, y);

      if (pixel.h > 113.5 && pixel.h <= 293.5) {
        pixel.h = 216;
      } else {
        pixel.h = 11;
      }

    }
  }

}

void Image::scale(double factor)
{

  PNG * temp = new PNG();

  temp->resize((unsigned)this->width()*factor,(unsigned)this->height()*factor);

  for (unsigned i = 0; i < temp->width(); i++){
    for (unsigned j = 0; j < temp->height(); j++){

      HSLAPixel & pix = temp->getPixel(i,j);
      pix = this->getPixel((unsigned)i/factor,(unsigned)j/factor);

    }
  }

  this->PNG::operator=(*temp);
  delete temp;

}

void Image::scale(unsigned w, unsigned h)
{

  double factor = 0;
  double factW = 0;
  double factH = 0;
  PNG * temp = new PNG();

  factW = w / this->width();
  factH = h / this->height();

  if (factW <= factH){
    factor = factW;
  } else {
    factor = factH;
  }

  temp->resize((unsigned)this->width()*factor,(unsigned)this->height()*factor);

  for (unsigned i = 0; i < temp->width(); i++){
    for (unsigned j = 0; j < temp->height(); j++){

      HSLAPixel & pix = temp->getPixel(i,j);
      pix = this->getPixel((unsigned)i/factor,(unsigned)j/factor);

    }
  }

  this->PNG::operator=(*temp);
  delete temp;

}
