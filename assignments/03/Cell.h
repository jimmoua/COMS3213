#ifndef CELL_H
#define CELL_H

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
