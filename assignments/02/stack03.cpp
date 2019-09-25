/* ----------------------------------------------------------------------------
 * Jim Moua
 * Program 2c
 * Due: 9/25/2019
 *
 * Input: None
 * Output: Elements within a stack followed by its reversal.
 *
 * Special Processing Requirements: None
 *
 * --------------------------------------------------------------------------*/

#include <iostream>
#include <stack>

void printStack(std::stack<int>);
void ReverseStack(std::stack<int>&, size_t);

int main() {
  /* Using two additional stacks to reverse elements of a given stack S */
  srand(time(0));
  constexpr size_t N = 10; // size of the size
  std::stack<int> S;

  /* Push N random numbers from range [1, 50] to the stack */
  for(size_t i = 0; i < N; i++) S.push(rand()%50+1);

  /* Print the original stack */
  std::cout << "The stack is as follows\n";
  printStack(S);

  /* Reverse the stack, and then print it */
  ReverseStack(S, S.size());
  std::cout << "\nHere is the stack after reversing\n";
  printStack(S);
  return 0;
}

/* ****************************************************************************
 * Function: void printStack(std::stack)
 *
 * Description:
 * This function will print the stack in LIFO order. If the stack is empty,
 * nothing will be printed.
 *
 * Preconditions:
 * None.
 *
 * Postconditions:
 * None
 * ***************************************************************************/
void printStack(std::stack<int> _s) {
  while(!_s.empty()) {
    std::cout << _s.top() << " ";
    _s.pop();
  }
  std::cout << std::endl;
}

/* ****************************************************************************
 * Function: voice ReverseStack(std::stack<int>& S, size_t size)
 *
 * Description:
 * This function takes a STL stack and reverses it using via recursion. The
 * size parameter is the size of the stack, once it hits 0 in the recursive
 * calls (the base case), it will resursively return thus pushing elements into
 * the original stack and making a reversal of the original stack.
 *
 * Preconditions:
 * None.
 *
 * Postconditions:
 * Since the STL stack is passed by reference the given stack parameter will be
 * changed.
 * ***************************************************************************/
void ReverseStack(std::stack<int>& S, size_t size) {
  static std::stack<int> ss;
  static bool moved = false;
  if(!moved) {
    while(!S.empty()) { 
      ss.push(S.top());
      S.pop();
    }
    moved = true;
  }
  if(size == 0) return;
  int tmp = ss.top();
  ss.pop();
  /* Via recurrsion! */
  ReverseStack(S, size-1);
  S.push(tmp);
}
