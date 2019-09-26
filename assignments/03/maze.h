#ifndef MAZE_H
#define MAZE_H
#include "Cell.h"
#include <bits/stdc++.h>
#include "Stack.h"

class Maze {
  public:
    Maze();
    ~Maze();
    void exitMaze();
  private:
    Cell currentCell, exitCell, entryCell;
    static constexpr char exitMarker  = 'e';
    static constexpr char entryMarker = 'm';
    static constexpr char visited     = '.';
    static constexpr char passage     = '0';
    static constexpr char wall        = '1';
    Stack<Cell> mazeStack;
    char** store;
    void pushUnvisited(int,int);
    friend std::ostream& operator<<(std::ostream&, const Maze&);
    int rows, cols;
};

Maze::Maze() {
  Stack<char*> mazeRows;
  char str[80], *s;
  int col, row = 0;
  printf("Enter a rectangular maze using the following characers:\n");
  printf("%c - entry\n", entryMarker);
  printf("%c - exit\n", exitMarker);
  printf("%c - wall\n", wall);
  printf("%c - passage\n", passage);
  printf("Enter one line at a time. End with Ctrl-d\n");

  while(std::cin >> str) {
    row++;
    cols = strlen(str);
    s = new char[cols+3];

    mazeRows.push(s);
    strcpy(s+1, str);
    s[0] = s[cols+1] = wall;
    s[cols+2] = '\0';
    if(strchr(s, exitMarker) != 0) {
      exitCell.x = row;
      exitCell.y = strchr(s,exitMarker) - s;
    }

    if(strchr(s,entryMarker) != 0) {
      entryCell.x = row;
      entryCell.y = strchr(s,entryMarker) - s;
    }
  }

  rows = row;
  store = new char*[rows+2];
  store[0] = new char[cols+3];
  for(; !mazeRows.empty(); row--) {
    store[row] = mazeRows.pop();
  }
  store[rows+1] = new char[cols+3];
  store[0][cols+2] = store[rows+1][cols+2] = '\0';
  for(col = 0; col <= cols+1; col++) {
    store[0][col] = wall;
    store[rows+1][col] = wall;
  }
}

void Maze::pushUnvisited(int row, int col) {
  if(store[row][col] == passage || store[row][col] == exitMarker) {
    mazeStack.push(Cell(row,col));
  }
}

void Maze::exitMaze() {
  /* Use row and col to mark and keep track of current location, and set the
   * starting location to be the entry cell. */
  int row, col;
  currentCell = entryCell;
  while(!(currentCell == exitCell)) {
    row = currentCell.x;
    col = currentCell.y;
    std::cout << *this;

    /* Mark the current location as visited */
    if(!(currentCell == entryCell)) {
      store[row][col] = visited;
    }

    /* Mark all adjacent nodes in the matrix as unvisited */
    pushUnvisited(row-1, col);
    pushUnvisited(row+1, col);
    pushUnvisited(row, col-1);
    pushUnvisited(row, col+1);

    /* If previous iteration of while loop gave us an empty stack, mouse failed
     * to get out of the maze */
    if(mazeStack.empty()) {
      std::cout << *this;
      std::cout << "Failure\n";
      return;
    }
    else currentCell = mazeStack.pop();
  }
  std::cout << *this;
  std::cout << "Success\n";
}

std::ostream& operator<<(std::ostream& os, const Maze& maze) {
  for(int row = 0; row <= maze.rows+1; row++) {
    os << maze.store[row] << std::endl;
  }
  os << std::endl;
  return os;
}

/* Destructor */
Maze::~Maze() {
  for(int i = 0; i < rows+2; i++) {
    delete [] this->store[i];
  }
  delete [] this->store;
}

#endif
