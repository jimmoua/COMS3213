#include <iostream>
#include <string>
#include <stack>
#include <cstring>

namespace {
  static long long times = 0;
}

template<typename T>
class Stack: public std::stack<T> {
  public:
    T pop() {
      /* The original is
       *   T tmp = top();
       * but there is no top from this class or any inherited */
      T tmp = std::stack<T>::top();
      std::stack<T>::pop();
      return tmp;
    }
};

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

class Maze {
  public:
    Maze();
    void exitMaze();
  private:
    Cell currentCell, exitCell, entryCell;
    const char exitMarker, entryMarker, visited, passage, wall;
    Stack<Cell> mazeStack;
    char** store;
    void pushUnvisited(int,int);
    friend std::ostream& operator<<(std::ostream&, const Maze&);
    int rows, cols;
};

Maze::Maze() : exitMarker('e'),
               entryMarker('m'),
               visited('.'),
               passage('0'),
               wall('1') {
  Stack<char*> mazeRows;
  char str[80], *s;
  int col, row = 0;
  std::cout << "Enter a rectangular maze using the following "
             << "characters:\nm - entry\ne - exit\n1 - wall\n0 - passage\n"
             << "Enter one line at a time; end with Ctrl-z:\n";

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
  store = new char* [rows+2];
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
  int row, col;
  currentCell = entryCell;
  while(!(currentCell == entryCell)) {
    times++;
    row = currentCell.x;
    col = currentCell.y;
    std::cout << *this;
    if(!(currentCell == entryCell)) {
      store[row][col] = visited;
    }
    pushUnvisited(row-1, col);
    pushUnvisited(row+1, col);
    pushUnvisited(row, col-1);
    pushUnvisited(row, col+1);
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

int main() {
  Maze().exitMaze();
  printf("%lld\n", times);
  return 0;
}
