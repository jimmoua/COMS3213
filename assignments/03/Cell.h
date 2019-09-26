#ifndef CELL_H
#define CELL_H

/* ****************************************************************************
 * Class: Cell
 *
 * Description:
 * This class acts as the simple structure to contain the x,y coordinates of
 * the entry cell, exit cell, and the current cell of the maze when the
 * exitMaze function is called.
 *
 * ***************************************************************************/
class Cell {
  public:
    Cell(int i = 0, int j = 0) {
      x = i; y = j;
    }
    bool operator==(const Cell& c) const {
      return (x == c.x && y == c.y);
    }
  private:
    int x, y;
    friend class Maze;
};

#endif
