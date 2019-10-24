/* -----------------------------------------------------------------------------
 *       Name: Jim Moua
 *   Due Date: Nov 1 2019
 * Program 04: Binary Search Trees and Manipulations via Recurrsion
 * ---------------------------------------------------------------------------*/
#ifndef BT_NODE_TYPE_H
#define BT_NODE_TYPE_H
#include <cstddef>

template<class T>
struct BTNodeType
{
  T item;
  BTNodeType<T>* left = nullptr;
  BTNodeType<T>* right = nullptr;
};

#endif
