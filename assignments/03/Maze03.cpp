/* ----------------------------------------------------------------------------
 *       Name: Jim Moua
 * Program 03: Maze03
 *        Due: 10/27/2019
 *
 * Description:
 * This one is exactly like Maze02.cpp, but instead of printing dots at the end
 * to show the entry to entry, we will represent it with '-' for traversals and
 * a '|' for a change in direction. In addition, it will not print the dead
 * ends.
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
 * the paths with a '.', and eventually, it will print the path it took to get
 * there.
 *
 *    example maze (final) output:
 *      1111111
 *      1e00001
 *      1110111
 *      1000001
 *      100m001
 *      1111111
 *         ↓
 *       (...)          I used ellipses to denote other maze prints
 *         ↓
 *      1111111
 *      1e--..1
 *      111|111
 *      1..|--1
 *      1..m-|1
 *      1111111
 * --------------------------------------------------------------------------*/
#include "maze03.h"

int main() {
  Maze().exitMaze();
}
