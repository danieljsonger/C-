#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image superman; superman.readFromFile("superman.png");
  Image space; space.readFromFile("space.png");
  Image rainbow; rainbow.readFromFile("rainbow.png");

  space.scale(800,800); rainbow.scale(600, 600); superman.scale(150,150);



  StickerSheet sheet(space,3);
  sheet.addSticker(superman,150,300);
  sheet.addSticker(rainbow, 0,0);

  std::cout << "Making PNG" << std::endl;
  
  sheet.render().writeToFile("out.png");

  return 0;
}
