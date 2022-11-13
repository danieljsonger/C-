#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    SquareMaze maze;
    maze.makeCreativeMaze(1000);
	cs225::PNG * actualOutput = maze.drawMaze();
	actualOutput->writeToFile("creative"+ string(".png"));
	delete actualOutput;
    return 0;
}
