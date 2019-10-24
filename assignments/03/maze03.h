#ifndef MAZE03_H
#define MAZE03_H
#include "Cell01.h"
#include "Stack01.h"
#include <cstring>
#include <iostream>
#include <vector>

/* ****************************************************************************
 * Class: Maze
 *
 * Description:
 * This is the simple structure that is used to contain the map, which is
 * represented by some ASCII characters. The original assignment in the book
 * assigned the const values of the markers in the default constructor, but I
 * set the values here in the class, since it much more convenient and the
 * formatting looks much nicer.
 *
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
    bool entryMarkerExists = false;
    Stack<Cell> mazeStack;
    char** store;
    void pushUnvisited(int,int);
    friend std::ostream& operator<<(std::ostream&, const Maze&);

    // Cost equals two because the current way the program is written, it does
    // not increment cost when we land on an entry marker or exit marker.
    // Therefore, we must account for those costs here. (According to the book,
    // we have to include these into the paths taken)
    int rows, cols;
};

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

  // This is just a dumb play with code, but I'm marking it like this for now...
  // Basically, if the current position it equal to the entry cell nodes, that
  // means the exit has found a pathway to the entry. However, we don't want to
  // call it quits just yet because there is a possibility that we still have
  // yet to calculate the longest path possible from the exit to the entry.

  // In order to consider the longest path, we have to consider a path whose
  // cost is the most expensive.

  if(Cell(row, col) == entryCell) entryMarkerExists = true;
  if(store[row][col] == passage || store[row][col] == entryMarker) {
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
  currentCell = exitCell;

  std::vector<Cell> path;


  // Let level be the node we start at (entryCell.x) If the level were to
  // increment by 1, that means we preformed a breadth-first search on the row,
  // and we descend downwards to perform more searches. While we search, we
  // should be concerned with the cost of the searches as this will be used to
  // compute the longest path to the entry.

  while(!(currentCell == entryCell)) {
    row = currentCell.x;
    col = currentCell.y;
    std::cout << *this;

    // If the marked area is not the exit cell, mark it as visited.
    if(!(currentCell == exitCell)) {
      path.push_back(Cell(currentCell));
      if(store[row][col] != entryMarker) {
        store[row][col] = visited;
      }
    }
    // I was going to have currentCell == exitCell here as well, but it would
    // seem that will never quite work because by the time the exitCell is met,
    // all... wait I still need to consider things such as is the entry is at the 
    else if(currentCell == entryCell || currentCell == exitCell) {
      path.push_back(Cell(currentCell));
    }

    // Push the nodes around the current into the stack. Consider reading the
    // comments from this function to see what gets pushed into the stack and
    // what does not get pushed into the stack
    pushUnvisited(row-1, col);  // North
    pushUnvisited(row+1, col);  // South
    pushUnvisited(row, col-1);  // West
    pushUnvisited(row, col+1);  // East

    /* If previous iteration of while loop gave us an empty stack, mouse failed
     * to get out of the maze */
    if(mazeStack.empty()) {
      std::cout << *this;
      std::cout << "Failure\n";
      return;
    }
    else {
      // t is the "old" cell
      Cell t = currentCell;
      // currentCell becomes a new one
      currentCell = mazeStack.pop();

      // Here, after dropping down a level, check to see if any dead ends need
      // to be subtracted from the cost.

      // If we need to remove things on the east (if dropped down)
      if(currentCell.x > t.x && currentCell.y < t.y) {
        for(int i = currentCell.y+1; i <= t.y; i++) {
          for(auto iter = path.begin(); iter!= path.end(); iter++) {
            if(*iter == Cell(t.x,i)) {
              path.erase(iter);
              break;
            }
          }
        }
      }
      // If we need to remove things on the west (if dropped down)
      else if(currentCell.x > t.x && currentCell.y > t.y) {
        for(int i = t.y; i <= currentCell.y-1; i++) {
          for(auto iter = path.begin(); iter!= path.end(); iter++) {
            if(*iter == Cell(t.x,i)) {
              path.erase(iter);
              break;
            }
          }
        }
      }
    }
  }
  
  // Here, we are getting the dead ends and adding them to the vector. The +2
  // offset is because we've surrounded the maze with a border of 1's. We can
  // either add an offset to rows,cols or add an offset to the indexes. Here,
  // I've chose to add offsets to the rows,cols instead of indices.
  std::vector<Cell> deadEnds;
  for(size_t i = 0; i < (size_t)rows+2; i++) {
    for(size_t j = 0; j < (size_t)cols+2; j++) {
      if(store[i][j] == passage) {
        deadEnds.push_back(Cell(i, j));

        // Commented the below -> After the success, pop the stack since it's
        // the exitk marker (should log first) and then proceed to traverse the
        // maze (for dead ends).
         store[i][j] = visited;
      }
    }
  }

  // Because the exit cell isn't pushed into the paths vector, we have to
  // manually do it here... Pop the next unvisited Cell into the current cell
  // so we can continue traversing.
  path.push_back(currentCell);
  currentCell = mazeStack.pop();
  std::cout << *this;


  entryMarkerExists = true;

  while(!mazeStack.empty()) {
    row = currentCell.x;
    col = currentCell.y;
    std::cout << *this;
    if(store[row][col] != entryMarker) {
      store[row][col] = visited;
    }
    
    pushUnvisited(row-1, col);  // North
    pushUnvisited(row+1, col);  // South
    pushUnvisited(row, col-1);  // West
    pushUnvisited(row, col+1);  // East

    currentCell = mazeStack.pop();

  }
  
  // Before printing, we will use an algorithm to change the dots into either a
  // dash or a vertical line.
  //
  // Let M be a any row within the maze.
  // Let N be the row below M, hence N = M+1
  // Convert all visited markers into dashes
  //
  // Once we have descended down to row N, we will use the column position to
  // determine where the vertical line marker should be.

  // First, set all the visited marks to the dash
  for(auto i = path.begin(); i != path.end(); i++) {
    if(store[i->x][i->y] != exitMarker && store[i->x][i->y] != entryMarker) {
      store[i->x][i->y] = '-';
      if(i->x != (i-1)->x) {
        store[i->x][i->y] = '|';
      }
    }
  }

  std::cout << *this;

  std::cout << "Success\n";
  
  printf("Path taken was: \n");
  for(const auto& i : path) {
    printf("[%d, %d] ", i.x, i.y);
  }
  printf("\n");
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

#endif
