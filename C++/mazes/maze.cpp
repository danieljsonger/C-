#include "maze.h"
#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <queue>
#include <stack>
#include <map>
#include <cmath>

using namespace std;
using cs225::PNG;

SquareMaze::SquareMaze()
{
    _height = 0;
    _width = 0;
}
void SquareMaze::makeMaze(int width, int height)
{  

    cells.clear();
    DisjointSets dset;
    _height = height;
    _width = width;

    for (int i = 0; i < height * width; i++)
    {
        cells.push_back(Cell());
    }
    dset.addelements(_width * _height);
    int count = 0;
    while (count < (_width * _height) - 1)
    {
        int random_x = rand() % (_width);
        int random_y = rand() % (_height);
        int dir_right = rand() % 2;
        if (dir_right == 0)
        {
            int neighbor = random_y * height + random_x + 1;
            if ( (!(random_x >= width -1)) && (dset.find(random_y * height + random_x) != dset.find(neighbor)))
            {
                cells[random_y * height + random_x].has_right = false;
                dset.setunion(random_y * height + random_x, neighbor);
                count++;
            }
        }
        else
        {
            int neighbor = (random_y + 1) * height + random_x;
            if ((!(random_y >= height-1)) && (dset.find(random_y * height + random_x) != dset.find(neighbor)))
            {
                cells[random_y * height + random_x].has_down = false;
                dset.setunion(random_y * height + random_x, neighbor);
                count++;
            }
        }

        //count++;
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
    if (dir == 0)
    {
        return !cells[x + y * _height].has_right;
    }
    if (dir == 1)
    {
        return !cells[x + y * _height].has_down;
    }
    if (dir == 2)
    {
        if (x  <= 0)
        {
            return false;
        }
        return !cells[(x + y * _height) - 1].has_right;
    }
    if (dir == 3)
    {
        if (y  <= 0)
        {
            return false;
        }
        return !cells[x + (y-1) * (_height)].has_down;
    }
    return false;
}
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
    if(dir){
    cells[x + y * _height].has_down = exists;
    }
    else{
    cells[x + y * _height].has_right = exists;
    }
}

PNG * SquareMaze::drawMaze() const {
	PNG * ret = new PNG(_width * 10 + 1, _height * 10 + 1);

	for (size_t i = 0; i < ret->height(); i++) {
		ret->getPixel(0, i).l = 0;
	}

	for (size_t i = 10; i < ret->width(); i++) {
		ret->getPixel(i, 0).l = 0;
	}

	for (size_t cell = 0; cell < cells.size(); cell++) {
		size_t x = cell % _width, y = cell / _width;

		if (cells[cell].has_right) {
			for (int i = 0; i <= 10; i++) {
				ret->getPixel((x + 1) * 10, y * 10 + i).l = 0;
			}
		}

		if (cells[cell].has_down) {
			for (int i = 0; i <= 10; i++) {
				ret->getPixel(x * 10 + i, (y + 1) * 10).l = 0;
			}
		}
	}

	return ret;
}

PNG * SquareMaze::drawMazeWithSolution() {
	PNG * maze = drawMaze();
	vector<int> path = solveMaze();
	
	int x = 5, y = 5;
	int endx = 0, endy = 0;

	
	for (int step : path) {
		switch (step) {
			case 0:
				for (int i = 0; i < 10; i++) {
					maze->getPixel(x++, y) = cs225::HSLAPixel(0, 1, 0.5, 1);
				}

				maze->getPixel(x, y) = cs225::HSLAPixel(0, 1, 0.5, 1);
				endx++;
				break;


			case 1:
				for (int i = 0; i < 10; i++) {
					maze->getPixel(x, y++) = cs225::HSLAPixel(0, 1, 0.5, 1);
				}

				maze->getPixel(x, y) = cs225::HSLAPixel(0, 1, 0.5, 1);
				endy++;
				break;


			case 2:
				for (int i = 0; i < 10; i++) {
					maze->getPixel(x--, y) = cs225::HSLAPixel(0, 1, 0.5, 1);
				}

				maze->getPixel(x, y) = cs225::HSLAPixel(0, 1, 0.5, 1);
				endx--;
				break;


			case 3:
				for (int i = 0; i < 10; i++) {
					maze->getPixel(x, y--) = cs225::HSLAPixel(0, 1, 0.5, 1);
				}

				maze->getPixel(x, y) = cs225::HSLAPixel(0, 1, 0.5, 1);
				endy--;
				break;


			default:
				std::cerr << "Something went wrong! :(" << std::endl;
		}
	}

	for (int k = 1; k <= 9; k++) {
		maze->getPixel(endx * 10 + k, (endy + 1) * 10).l = 1;
	}

	return maze;
}

vector<int> SquareMaze::solveMaze() {
	vector<int> path;
	int size = cells.size();

	map<int, Step> parents;
	vector<bool> visited(cells.size(), false);
	std::stack<int> bfs;

	bfs.push(0);
	visited[0] = true;

	while (!bfs.empty()) {
		int front = bfs.top();
		bfs.pop();
		visited[front] = true;

        int x = front % _width;
        int y = front / _width;
		int right = front + 1,
			down = front + _width,
			left = front - 1,
			up = front - _width;
		if (canTravel(x,y, 0) && !visited[right]) {
			bfs.push(right);
			parents[right] = {front, 0};
		}

		if (canTravel(x,y, 1) && !visited[down]) {
			bfs.push(down);
			parents[down] = {front, 1};
		}

		if (canTravel(x,y,2) && !visited[left]) {
			bfs.push(left);
			parents[left] = {front, 2};
		}

		if (canTravel(x, y, 3) && !visited[up]) {
			bfs.push(up);
			parents[up] = {front, 3};
		}
	}

	for (int i = 0; i < _width; i++) {
		vector<int> temp;
		int start = 0, end =_width * (_height -1) + i;

		while (end != start) {
			temp.push_back(parents[end].dir);
			end = parents[end].pos;
		}


		if (temp.size() > path.size()) {
			path = temp;
		}
	}
	
	std::reverse(std::begin(path), std::end(path));

	return path;
}

PNG * SquareMaze::drawCreativeMaze() const {
    PNG * ret = new PNG(_width * 10 + 1, _height * 10 + 1);

	for (size_t i = 0; i < ret->height(); i++) {
		ret->getPixel(0, i).l = 0;
	}

	for (size_t i = 10; i < ret->width(); i++) {
		ret->getPixel(i, 0).l = 0;
	}

	for (size_t cell = 0; cell < cells.size(); cell++) {
        size_t x = 0;
        int temp_cell = cell,temp_height = _height;
        while(temp_cell > 0){
            x++;
            temp_cell -= temp_height;
            temp_height -= 1;
        }
		size_t y = temp_cell * -1 ;

		if (cells[cell].has_right) {
			for (int i = 0; i <= 10; i++) {
				ret->getPixel((x + 1) * 10, y * 10 + i).l = 0;
			}
		}

		if (cells[cell].has_down) {
			for (int i = 0; i <= 10; i++) {
				ret->getPixel(x * 10 + i, (y + 1) * 10).l = 0;
			}
		}
	}

	return ret;
}

void SquareMaze::makeCreativeMaze(int height){

    // added
    int width = height;

    cells.clear();
    DisjointSets dset;
    _height = height;
    _width = width;

    for (int i = 0; i < height * width; i++)
    {
        cells.push_back(Cell());
    }
    dset.addelements(_width * _height);

    int radius = int(sqrt((_width/4)*(_width/4)+(_height/4)*(_height/4)));
    std::cout << "rad: " << int(3.14*(radius-2)*(radius-2) - 1) << std::endl;
    int x_naught = _width/2 - 1;
    int y_naught = _height/2;

    for (int x = 0; x < _width; x++){
        for(int y = 0; y < _height; y++){

            if(int(sqrt((x-x_naught)*(x-x_naught) + (y-y_naught)*(y-y_naught))) >= radius+3){
                cells[y*_height + x].has_down = false;
                cells[y*_height + x].has_right = false;
            } else {
                cells[y*_height + x].has_down = true;
                cells[y*_height + x].has_right = true;
            }

            // Draw pathway in
            // if (y == 1 && x <= _width/2 && x > 0) { cells[y*_height + x].has_down = true; }
            // if (y == 0 && x <= _width/2 + 1 && x > 1) { cells[y*_height + x].has_down = true; }
            // if (x == width/2 && y <= (_height/2 - radius) && y > 1) { cells[y*_height + x].has_right = true; }
            // if (x == width/2 + 1 && y <= (_height/2 - radius) && y > 0) { cells[y*_height + x].has_right = true; }
            // if (x == 1 && y == 0) { cells[y*_height + x].has_right = true; cells[y*_height + x].has_down = false; }
            // if (x == 0 && y == 0) { cells[y*_height + x].has_down = true; }
            // if (x == 0 && y == 1) { cells[y*_height + x].has_right = true; }
            // // Draw pathway out
            // if (y == _height-2 && x >= _width/2 + 1 && x < _width-2) { cells[y*_height + x].has_down = true; }
            // if (y == _height-3 && x >= _width/2 + 2 && x < _width-1) { cells[y*_height + x].has_down = true; }
            // if (x == width/2 && y >= (_height/2 - radius)+1 && y < _height - 1) { cells[y*_height + x].has_right = true; }
            // if (x == width/2 + 1 && y >= (_height/2 - radius)+1 && y < _height - 2) { cells[y*_height + x].has_right = true; }
            // if (x == _width-1 && y == _height-1) { cells[y*_height + x].has_right = true; }
            // if (x == _width-3 && y == _height-1) { cells[y*_height + x].has_right = true; cells[y*_height + x].has_down = false; }
            // if (x == _width-1 && y == _height-2) { cells[y*_height + x].has_down = true; }
            // if (x == _width-2 && y == _height-2) { cells[y*_height + x].has_right = true; }
            // if (x == _width-2 && y == _height-1) { cells[y*_height + x].has_down = true; }

        }
    }

    for (int x = 0; x <= x_naught+1; x++){
        
        if (x == 0) {
            // top
            cells[x].has_down = true;

            // bottom
            cells[((_width-1)*_height)-x].has_down = true;
            cells[(_width*_height)-x].has_right = false;
            cells[(_width*_height)-x].has_down = true;


        } else if (x == 1) {
            // top
            cells[x].has_down = false;
            cells[x].has_right = true;
            cells[x+1].has_down = true;
            cells[x+_width].has_right = false;
            cells[x+_width-1].has_right = true;
            cells[x+_width].has_down = true;
            dset.setunion(0,x);
            dset.setunion(x,x+_width);
            dset.setunion(x+_width,x+_width+1);
            
            // bottom 
            cells[((_width)*_height)-x-1].has_right = true;
            cells[((_width-2)*_height)-x].has_down = true;
            cells[((_width)*_height)-x].has_down = true;
            cells[((_width-1)*_height)-x-1].has_right = true;
            dset.setunion(_height*_width,(_height*_width)-x);
            dset.setunion(_height*_width,(_height*(_width-1))-x);
            dset.setunion((_height*(_width-1))-x,(_height*(_width-1))-x-1);
        } else if (x == x_naught+1) {
            // top
            cells[x].has_down = true;
            // bottom 
            cells[((_width-1)*_height)-x].has_down = true;
            for (int y = 1; y <= y_naught-radius+5; y++){
                // top
                cells[y*_height+x].has_down = false;
                cells[y*_height+x].has_right = true;
                if (y > 1) { cells[y*_height+x-1].has_right = true; }
                dset.setunion((y*_height)+x,((y+1)*_height)+x);

                // bottom 
                cells[(_width*(_height-y-1))-x].has_down = false;
                if (y > 1) { cells[(_width*(_height-y))-x].has_right = true; }
                cells[(_width*(_height-y))-x-1].has_right = true;
                dset.setunion(((_width-1)*(_height-y))-x,((_width-1)*(_height-y-1))-x);
            }
        } else {
            // top
            dset.setunion(_width+x,_width+x+1);
            cells[x].has_right = false;
            cells[x+_width].has_down = true;
            cells[x].has_down = true;
            
            // bottom 
            dset.setunion(((_width-1)*_height)-x,((_width-1)*_height)-x-1);
            cells[((_width-1)*_height)-x].has_right = false;
            cells[((_width-1)*_height)-x].has_down = true;
            cells[((_width-2)*_height)-x].has_down = true;
        }
    }

    int count = 0;
    while (count < int(3.14*(radius-4)*(radius-4) - 1))
    {
        // std::cout << count << " "; 
        int random_x = rand() % (2*(radius-4)) + (x_naught-radius) + 4; // center of this might be off by one

        int random_y = rand() % (2*int(sqrt(radius*radius - (random_x-x_naught)*(random_x-x_naught))-5)) + y_naught - int(sqrt(radius*radius - (random_x-x_naught)*(random_x-x_naught))) + 5;
        int dir_right = rand() % 2;

        if (dir_right == 0)
        {
            int neighbor = random_y * height + random_x + 1;
            if ( (!(random_x >= x_naught+radius-1) && !(random_x <=x_naught-radius+1)) && (dset.find(random_y * height + random_x) != dset.find(neighbor)))
            {
                cells[random_y * height + random_x].has_right = false;
                dset.setunion(random_y * height + random_x, neighbor);
                count++;
            }
        }
        else
        {
            int neighbor = (random_y + 1) * height + random_x;
            if ((!(random_y >= _height-1)) /*y_naught + sqrt(radius*radius - (random_x-x_naught)*(random_x-x_naught))) && !(random_y <= y_naught - sqrt(radius*radius - (random_x-x_naught)*(random_x-x_naught))))*/ && (dset.find(random_y * height + random_x) != dset.find(neighbor)))
            {
                cells[random_y * height + random_x].has_down = false;
                dset.setunion(random_y * height + random_x, neighbor);
                count++;
            }
        }
    }

    dset.setunion(0,_height);
    dset.setunion(0,_height+1);



    // cells.clear();

    // DisjointSets dset;
    // _height = height;
    // _width = height;

    // int area = _height * _width / 2;
    // // int area = int((height+1 * _width /2));

    // for (int i = 0; i < area; i++) {
    //     cells.push_back(Cell());
    // }
 
    // dset.addelements(area) ;

    // int count = 0;
    // while (count < (area - 1)) {

    //     int random_y = rand() % (_width);
    //     int random_x = rand() % (_height);
    //     int dir_right = rand() % 2;

    //     if (dir_right == 0) {
    //         int neighbor = random_y * height + random_x + 1;
    //         if ( (!(random_x >= _width - sqrt(random_y*random_y+random_x*random_x) -1)) && (dset.find(random_y * height + random_x) != dset.find(neighbor))) {
    //             cells[random_y * height + random_x].has_right = false;
    //             dset.setunion(random_y * height + random_x, neighbor);
    //             count++;
    //         }
    //     } else {
    //         int neighbor = (random_y + 1) * height + random_x;
    //         if ((!(random_y >= _height - 1)) && (dset.find(random_y * height + random_x) != dset.find(neighbor))) {
    //             cells[random_y * height + random_x].has_down = false;
    //             dset.setunion(random_y * height + random_x, neighbor);
    //             count++;
    //         }
    //     }

    // }
}
    // while (count < (_width * _height) - 1)
    // {
    //     int random_x = rand() % (_width);
    //     int random_y = rand() % (_height);
    //     int dir_right = rand() % 2;
    //     if (dir_right == 0)
    //     {
    //         int neighbor = random_y * height + random_x + 1;
    //         if ( (!(random_x >= width -1)) && (dset.find(random_y * height + random_x) != dset.find(neighbor)))
    //         {
    //             cells[random_y * height + random_x].has_right = false;
    //             dset.setunion(random_y * height + random_x, neighbor);
    //             count++;
    //         }
    //     }
    //     else
    //     {
    //         int neighbor = (random_y + 1) * height + random_x;
    //         if ((!(random_y >= height-1)) && (dset.find(random_y * height + random_x) != dset.find(neighbor)))
    //         {
    //             cells[random_y * height + random_x].has_down = false;
    //             dset.setunion(random_y * height + random_x, neighbor);
    //             count++;
    //         }
    //     }

    //     //count++;
    // }