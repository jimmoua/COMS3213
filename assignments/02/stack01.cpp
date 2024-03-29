/* ----------------------------------------------------------------------------
 * Jim Moua
 * Program 2a
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

/* Function prototypes */
void printStack(std::stack<int>);
void ReverseStack(std::stack<int>&);

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
  ReverseStack(S);
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
 * Function: voice ReverseStack(std::stack<int>& S)
 *
 * Description:
 * This function takes a STL stack and reverses it.
 *
 * Preconditions:
 * None.
 *
 * Postconditions:
 * Since the STL stack is passed by reference the given stack parameter will be
 * changed.
 * ***************************************************************************/
void ReverseStack(std::stack<int>& S) {
  /* Below are the two additional stacks */
  std::stack<int> s1;
  std::stack<int> s2;

  /* Add from the original stack to the first stack. This will reverse it */
  while(!S.empty()) {
    s1.push(S.top());
    S.pop();
  }

  /* Add from the first stack to the second stack. This will return it to its
   * original. */
  while(!s1.empty()) {
    s2.push(s1.top());
    s1.pop();
  }

  /* Add from the second stack to the original. This will reverse it again */
  while(!s2.empty()) {
    S.push(s2.top());
    s2.pop();
  }
}
