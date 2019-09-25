#include <iostream>
#include <string>
#include <stack>

template<typename T>
class Stack: public std::stack<T> {
  public:
    T pop() {
      T tmp = top();
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
      return x == c.x && x == c.y;
    }
};
