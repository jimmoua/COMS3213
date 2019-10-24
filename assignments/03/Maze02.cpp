/* ----------------------------------------------------------------------------
 *       Name: Jim Moua
 * Program 03: Maze02
 *        Due: 10/27/2019
 *
 * Description:
 * A maze program where the entry is marked back to entry marker (or the
 * mouse).
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
 *        e0000
 *        11011
 *        00000
 *        00m00
 *
 * Output:
 * After inputting, the program will surround the maze with a wall of 1's.
 * Will also print each step the exit maps to the mouse or entry cell denoting
 * the paths with a '.'
 *
 * After this, it will print (row, col) markers of the path that was taken from
 * the exit to the entry marker as well as the dead ends.
 *
 *    example maze output:
 *     1111111
 *     1e00001
 *     1110111
 *     1000001
 *     100m001
 *     1111111
 *        ↓
 *      (...)          I used ellipses to denote other maze prints
 *        ↓
 *     1111111
 *     1e....1
 *     111.111
 *     1.....1
 *     1..m..1
 *     1111111
 *
 *     Path taken was
 *     [1, 1] [1, 2] [1, 3] [2, 3] [3, 3] [3, 4] [3, 5] [4, 5] [4, 4] [4, 3] 
 *
 *     Dead ends are at
 *     [3, 1] [3, 2] [4, 1] [4, 2]
 * --------------------------------------------------------------------------*/
#include "maze02.h"

int main() {
  Maze().exitMaze();
}
