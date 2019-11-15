/* ----------------------------------------------------------------------------
 *       Name: Jim Moua
 * Program 03: Maze01
 *        Due: 10/27/2019
 *
 * Description:
 * A maze program where a mouse will try to escape a given input maze.
 *
 * Input:
 * The input are lines that will represent an N×M matrix.
 * with values of
 *          m   →  entry marker
 *          e   →  exit marker
 *          0   →  passage marker
 *          1   →  wall marker
 *
 *    example maze input:
 *      
 *       e0000
 *       11011
 *       00000
 *       00m00
 *
 * Output:
 * Will print each step the mouse takes in order to escape the maze by denoting
 * the paths with a '.' - meaning that the mouse had traversed it.
 *
 *    example maze (final) output:
 *     1111111     1111111
 *     1e00001  →  1e....1
 *     1110111  →  111.111
 *     1000001  →  1.....1
 *     100m001  →  1..m..1
 *     1111111     1111111
 * --------------------------------------------------------------------------*/

#include <iostream>
#include <cstring>
#include <stack>

/* ****************************************************************************
 * Class: Stack
 *
 * Description:
 * This inherits the std::stack<> class from the STL. All it does is have its
 * own overide function of pop. From the STL, pop returns nothing, but we
 * implemented this pop in order to return the top of the stack before actually
 * discarding it.
 *
 * ***************************************************************************/
template<typename T>
class Stack: public std::stack<T> {
  public:
    T pop() {
      T tmp = std::stack<T>::top();
      std::stack<T>::pop();
      return tmp;
    }
};

/* ----------------------------------------------------------------------------
 * Class: Cell
 *
 * Description:
 * This class acts as the simple structure to contain the x,y coordinates of
 * the entry cell, exit cell, and the current cell of the maze when the
 * exitMaze function is called.
 * --------------------------------------------------------------------------*/
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

/* ****************************************************************************
 * Class: Maze
 *
 * Description:
 * This is the simple structure that is used to contain the map, which is
 * represented by some ASCII characters. The original assignment in the book
 * assigned the const values of the markers in the default constructor, but I
 * set the values here in the class, since it much more convenient and the
 * formatting looks much nicer.
 * ***************************************************************************/
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

////////////////////////////////////////////////////////////////////////////////
// Function:
// main()
////////////////////////////////////////////////////////////////////////////////
int main() {
  Maze().exitMaze();
  return 0;
}

/* ****************************************************************************
 * Function: Maze::Maze()
 *
 * Description:
 * This is the default constructor of the Maze class. It will take inputs of N
 * lines and the user will stop these inputs by pressing ^d (ctrl-d). The
 * original assignment as per the book was to have the users exit by pressing
 * ^z (ctrl-z), but on many Linux systems, that is the shortcut to pause a
 * program and "minimize" it.
 *
 * Preconditions:
 * None
 *
 * Postconditions:
 * Since this is the constructor, an obvious thing it does is some small
 * "set-up" stuff.  After taking N lines of input, which should represent the
 * maze, the constructor will surround that maze with walls which represent a
 * '1'.
 *
 * ***************************************************************************/
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

/* ****************************************************************************
 * Function: Maze::pushUnvisited(int row, int col)
 *
 * Description:
 * Pushes the x,y locations of the unvisted nodes into the maze stack.
 *
 * Preconditions:
 * row and col are representations of the unvisited nodes if we represent the
 * maze in matrix form.
 *
 * Postconditions:
 * If the surrounding node of the current cell is not a wall nor is it a
 * visited area, we will push that surround node into the mazeStack. This means
 * only the locations of unvisited '0' and the exit marker 'e' will be pushed
 * into the stack.
 *
 * ***************************************************************************/
void Maze::pushUnvisited(int row, int col) {
  if(store[row][col] == passage || store[row][col] == exitMarker) {
    mazeStack.push(Cell(row,col));
  }
}

/* ****************************************************************************
 * Function: void Maze::exitMaze()
 *
 * Description:
 * This will emulate the mouse 'e' escaping the maze.
 *
 * Preconditions:
 * None
 *
 * Postconditions:
 * This will invoke the pushUnivisted functions and pop the mazeStack until
 * there are no more contents in it.
 *
 * ***************************************************************************/
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
    else {
      currentCell = mazeStack.pop();
    }
  }
  std::cout << *this;
  std::cout << "Success\n";
}

/* ****************************************************************************
 * Function: std::ostream& operator<<(std::ostream& os, const Maze& maze)
 *
 * Description:
 * Prints the maze.
 *
 * Preconditions:
 * None
 *
 * Postconditions:
 * None
 *
 * ***************************************************************************/
std::ostream& operator<<(std::ostream& os, const Maze& maze) {
  for(int row = 0; row <= maze.rows+1; row++) {
    os << maze.store[row] << std::endl;
  }
  os << std::endl;
  return os;
}

/* ****************************************************************************
 * Function: Maze::~Maze()
 *
 * Description:
 * Goes through store variable and deallocates them, since they were
 * dynamically allocated in the constructor.
 *
 * Preconditions:
 * An instance of the Maze class goes out of scope.
 *
 * Postconditions:
 * store is unallocated properly.
 *
 * ***************************************************************************/
Maze::~Maze() {
  for(int i = 0; i < rows+2; i++) {
    delete [] this->store[i];
  }
  delete [] this->store;
}
