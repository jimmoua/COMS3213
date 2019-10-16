#ifndef STACK01_H
#define STACK01_H
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

#endif
