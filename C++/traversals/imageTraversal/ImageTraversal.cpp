#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() 
{
  /** @todo [Part 1] */
  it_ = NULL;
}
/**
 * Non-default constuctor.
 **/
ImageTraversal::Iterator::Iterator(PNG png, Point start, double tolerance, ImageTraversal *traversal)
{
  current = start;
  png_ = png;
  start_ = start;
  it_ = traversal;
  tolerance_ = tolerance;
  // visit = new bool *[png.width()];

  for (unsigned i = 0; i < png.width(); i++){
    // visit[i] = new bool [png.height()];
    for (unsigned j = 0; j < png.height(); j++){

      visit[Point(i,j)] = false;
      // visit[i][j] = false;
      // visit.insert(std::pair<Point, bool>(Point(i,j), false));

    }

  }
  if ((start_.y < png.height()) && (start_.x < png.width())) {

    // visit.insert(std::pair<Point, bool>(Point(start_.x,start_.y), true));
    visit[current] = true;
  } else {
    it_ = NULL;  // Destroy iterator?
  }
}

// ImageTraversal::Iterator::~Iterator() 
// {
//   for (unsigned i = 0; i < png_.width(); i++){
//     delete visit[i];
//   }
//   delete visit;
//   this->std::iterator<std::forward_iterator_tag, Point>::~iterator();
// }


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
// visit[Point(current.x + 1, current.y)]
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  // if (current.x < png_.width() - 1){
  //   if ((calculateDelta(png_.getPixel(current.x + 1, current.y), png_.getPixel(start_.x,start_.y)) < tolerance_) && (visit[current.x + 1][current.y] == false)){
  //     Point p(current.x + 1, current.y);
  //     it_->add(p);
  //   }
  // }
  // if (current.y < png_.height() - 1){
  //   if ((calculateDelta(png_.getPixel(current.x, current.y + 1), png_.getPixel(start_.x,start_.y)) < tolerance_) && (visit[current.x][current.y + 1] == false)){
  //     Point p(current.x, current.y + 1);
  //     it_->add(p);
  //   }
  // }
  // if (current.x > 0){
  //   if ((calculateDelta(png_.getPixel(current.x - 1, current.y), png_.getPixel(start_.x, start_.y)) < tolerance_) && (visit[current.x - 1][current.y] == false)){
  //     Point p(current.x - 1, current.y);
  //     it_->add(p);
  //   }
  // }
  // if (current.y > 0){
  //   if ((calculateDelta(png_.getPixel(current.x, current.y - 1), png_.getPixel(start_.x, start_.y)) < tolerance_) && (visit[current.x][current.y - 1] == false)){
  //     Point p(current.x, current.y - 1);
  //     it_->add(p);
  //   }
  // }

  // if (it_->empty()){
  //   it_ = NULL;
  //   return * this;
  // }

  // current = it_->pop();

  // while (visit[current.x][current.y]){

  //   if (it_->empty()){
  //     it_ = NULL;
  //     return * this;
  //   }
  //   current = it_->pop();

  // }

  // visit[current.x][current.y] = true;
  // return * this;

  /** @todo [Part 1] */
  HSLAPixel & start = png_.getPixel(start_.x, start_.y);
  if (current.x < png_.width() - 1) {
    if (visit[Point(current.x+1,current.y)] == false && calculateDelta(png_.getPixel(current.x+1, current.y), start) < tolerance_) {
      Point p(current.x + 1, current.y);
      it_->add(p);
    }
  }
  if (current.y < png_.height() - 1) {
    if (visit[Point(current.x,current.y+1)] == false && calculateDelta(png_.getPixel(current.x, current.y+1), start) < tolerance_) {
      Point p(current.x, current.y+1);
      it_->add(p);
    }
  }
 
  if (current.x > 0) {
    if (visit[Point(current.x-1,current.y)] == false && calculateDelta(png_.getPixel(current.x-1, current.y), start) < tolerance_) {
      Point p(current.x - 1, current.y);
      it_->add(p);
    }
  }
 
  if (current.y > 0) {
    if (visit[Point(current.x,current.y-1)] == false && calculateDelta(png_.getPixel(current.x, current.y-1), start) < tolerance_) {
      Point p(current.x, current.y - 1);
      it_->add(p);
    }
  }
 
  //Remove traversal if it's empty
  if (it_->empty()) {
    it_ = nullptr;
    return *this;
  }
 
  while (visit[current]) {
    if (it_->empty()) {
      it_ = nullptr;
      return *this;
    }
 
    current = it_->pop();
  }
 
  visit[current] = true;
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (!other.it_ && !this->it_){  // if NOR then false
    return false;
  }
  if ((!this->it_ && other.it_) || (!other.it_ && this->it_)) {  // if XOR then true
    return true;
  } else {
    return other.it_ != this->it_;
  }

}

