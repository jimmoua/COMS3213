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
#include "maze01.h"

int main() {
  Maze().exitMaze();
}
