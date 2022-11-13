#ifndef _MAZE_H_
#define _MAZE_H_

#include <vector>
#include <unordered_map>
#include "dsets.h"
#include "cs225/PNG.h"

class SquareMaze{
    struct Cell{
        bool has_right;
        bool has_down;
        Cell(){
            has_right = true;
            has_down = true;
        }
        
    };
    struct Step {
			int pos;
			int dir;
	};
    
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        std::vector<int> solveMaze();
        void setWall(int x, int y, int dir, bool exists);
        cs225::PNG * drawMaze() const;
        cs225::PNG * drawMazeWithSolution();
        void solver(std::vector<int> vect, int x, int y, std::vector<int> & ans);
        cs225::PNG* drawCreativeMaze() const;
        cs225::PNG* drawCreativeMazeWithSolution();
        void makeCreativeMaze(int height);

        int dist( int i, int j, int w, int h) const;

    private:
        std::vector<std::vector<int>> maze;
        std::vector<Cell> cells;
        int _height;
        int _width;


};

#endif