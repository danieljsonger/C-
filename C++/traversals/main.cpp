
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  PNG png;
  png.readFromFile("tests/i.png");
  FloodFilledImage flood(png);

  HSLAPixel p0(32, 1, .5, 1);
  HSLAPixel p1(248, 1, .28, 1);

  BFS bfs(png, Point(100, 50), 0.5);
  MyColorPicker stripe0(p0,p1, 40);
  flood.addFloodFill( bfs, stripe0 );

  DFS dfs(png, Point(100, 50), 0.5);
  MyColorPicker stripe1(p0,p1, 60);
  flood.addFloodFill( dfs, stripe1 );


  Animation animation = flood.animate(1000);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
