#ifndef STACK_H
#define STACK_H
#include <stack>

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
