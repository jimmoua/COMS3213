/* -----------------------------------------------------------------------------
 *       Name: Jim Moua
 *   Due Date: Nov 1 2019
 * Program 04: Binary Search Trees and Manipulations via Recurrsion
 * ---------------------------------------------------------------------------*/
#ifndef BST_TYPE_H
#define BST_TYPE_H
#include "BTNodeType.h"
#include <cstddef>
#include <ostream>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sstream>

enum TravType { PRE, POST, IN };

template<class T>
class BSTType
{
  public:
    BSTType();
    BSTType(const BSTType<T>&);
    const BSTType<T>& operator=(const BSTType<T>&);
    virtual ~BSTType();
    bool empty() const;
    void erase(const T&);
    bool find(const T&) const;
    void insert(const T&);
    size_t size() const;
    void traverse(std::ostream&, TravType) const;

  protected:
    BTNodeType<T>* root = nullptr;
    size_t count = 0;

  private:
    void copy(BTNodeType<T>*&, BTNodeType<T>*);
    void destroy(BTNodeType<T>*&);
    void erase(const T&, BTNodeType<T>*&);
    bool find(const T&, BTNodeType<T>*) const;
    void inorder(std::ostream&, BTNodeType<T>*) const;
    void insert(const T&, BTNodeType<T>*&);
    void postorder(std::ostream&, BTNodeType<T>*) const;
    const T& predecessor(BTNodeType<T>*);
    void preorder(std::ostream&, BTNodeType<T>*) const;
};

/* ----------------------------------------------------------------------------
 * Function:
 *   BSTType<T>::BSTType()
 *
 * Description:
 *   The default constructor of the class.
 *
 * Preconditions:
 *   An object of the BSTType class is instantiated without any parameters.
 *
 * Postconditions:
 *   Does not do anything. The values of root, left, and right are defined to
 *   nullptr in the class already (since we are using C++ 11).
 * --------------------------------------------------------------------------*/
template<class T>
BSTType<T>::BSTType() {  }

/* ----------------------------------------------------------------------------
 * Function:
 *   BSTType<T>::BSTType(const BSTType<T>&)
 *
 * Description:
 *   The copy constructor. Performs deep copy by invoking the copy function.
 *
 * Preconditions:
 *   An object of the BSTType class is instantiated and another object of the
 *   same class is passed as an argument into the copy constructor.
 *
 * Postconditions:
 *   The newly instantiated object is provided with its own hard copy of the
 *   source tree.
 * --------------------------------------------------------------------------*/
template<class T>
BSTType<T>::BSTType(const BSTType<T>& src)
{
  copy(this->root, src.root);
}

/* ----------------------------------------------------------------------------
 * Function:
 *   const BSTType<T>& BSTType<T>::operator=(const BSTType<T>&)
 *
 * Description:
 *   The assignment operator overload. Performs deep copy by invoking the copy
 *   function.
 *
 * Preconditions:
 *   The only argument is the source that is going to be copied from.  In order
 *   to invoke this operator overload, place the source on the right-hand side
 *   of the assignment operator and the tree that will be copied to on the
 *   left-hand side.
 *
 * Postconditions:
 *   The object that is the left-hand side of the assignment operator will have
 *   it's own copy of the object on the right-hand side of the assignment
 *   operator.
 * --------------------------------------------------------------------------*/
template<class T> // public
const BSTType<T>& BSTType<T>::operator=(const BSTType<T>& src)
{
  // If not empty, destroy first.
  if(!this->empty())
  {
    this->destroy(this->root);
    this->count = 0;
  }
  copy(this->root, src.root);
  return *this;
}

/* ----------------------------------------------------------------------------
 * Function:
 *   BSTType<T>::~BSTType()
 *
 * Description:
 *   Destructor of the class. Traverses the tree and deallocates everything
 *   that was dynamically allocated.
 *
 * Preconditions:
 *   The object goes out of scope.
 *
 * Postconditions:
 *   This will free/deallocate memory that was allocated on the heap.
 * --------------------------------------------------------------------------*/
template<class T> BSTType<T>::~BSTType() { destroy(root); }

/* ----------------------------------------------------------------------------
 * Function:
 *   bool BSTTyppe<T>::empty() const
 *
 * Description:
 *   This function returns a bool value. The returned bool value is true if the
 *   tree is empty. If the returned bool value is false, there exists items in
 *   the tree. This function is also a true one-liner function.
 *
 * Preconditions: None.
 *
 * Postconditions: None.
 * --------------------------------------------------------------------------*/
template<class T> bool BSTType<T>::empty() const { return (this->count == 0); }

/* ----------------------------------------------------------------------------
 * Function:
 *   BSTType<T>::erase(const T&)
 *
 * Description:
 *   This function will remove an item from the tree by invoking the
 *   recursion function of erase.
 *
 * Preconditions:
 *   None.
 *
 * Postconditions:
 *   If an item is found, it will erase the item from the tree. If
 *   the item is not found, nothing will be modified.
 * --------------------------------------------------------------------------*/
template<class T> // public
void BSTType<T>::erase(const T& item) { erase(item, root); }

/* ----------------------------------------------------------------------------
 * Function:
 *   BSTType<T>::find(const T&) const
 *
 * Description:
 *   This will find an item in the tree if it exists. If the item is found, the
 *   function returns true. If the item is not found, the function returns
 *   false.
 *
 * Preconditions:
 *   None.
 *
 * Postconditions:
 *   Does not modify anything.
 * --------------------------------------------------------------------------*/
template<class T>
bool BSTType<T>::find(const T& item) const { return find(item, root); }

/* ----------------------------------------------------------------------------
 * Function:
 *   bool BSTType<T>::find(const T&, BTNodeType<T>*) const
 *
 * Description:
 *   Find function that is used to find the item via recurrsion.
 *
 * Preconditions:
 *   The find(const T&) is invoked somewhere in the program. This
 *   causes the reccursive function to be called.
 *
 * Postconditions:
 *   Does not modify anything.
 * --------------------------------------------------------------------------*/
template<class T>
bool BSTType<T>::find(const T& item, BTNodeType<T>* obj) const
{
  if(obj != nullptr)
  {
    if(obj->item == item)
      return true;
    else if(item < obj->item)
      /* If the left isn't a nullptr and the item that we are trying
       * to find less than the left item */
      return find(item, obj->left);
    else if (item > obj->item)
      /* If the left isn't what we're looking for, we are going to
       * check the right to see if it's nullptr. If it isn't, we will
       * traverse the right branches instead. */
      return find(item, obj->right);
  }
  return false;
}

/* ----------------------------------------------------------------------------
 * Function:
 *   BSTType<T>::insert(const T&)
 *
 * Description:
 *   The non-recursive function of insert. This insert function will
 *   invoke the recursive function of insert.
 *
 * Preconditions:
 *   The argument passed into the list is the item to be inserted into the
 *   tree.
 *
 * Postconditions:
 *   The tree is modified such that the item is inserted into the tree. The
 *   count of items that are in the tree is increased by 1.
 * --------------------------------------------------------------------------*/
template<class T> // public
void BSTType<T>::insert(const T& item)
{
  /* Here, an item needs to be inserted. When the insert function is first
   * invoked, it will check to see if the root node is nullptr.  If the root
   * node is nullptr, dynamically allocate memory for it and then set the
   * root->item to the item that is going to be inserted into the tree.
   *
   * If the list, however, is not empty, then similar to the find function, and
   * then insert where necessary
   *
   * It's going to look something like this: Say we want to insert a value of
   * 10 into list, and assume the list is list.
   *
   * Item to insert: 10
   * let NP = nullptr
   *
   *         [NP] ← This means we are going to insert it here
   *        /    \
   *      [NP]  [NP]
   *  
   * Tree after insertion...
   *         [10]
   *        /    \
   *      [NP]  [NP]
   *
   * The left and right still are nullptr. If we wish to insert more, that
   * means there will be more traversal, and we have to rely on recursion to
   * determine where the item should now be inserted
   * */
  insert(item, root);
}

/* ----------------------------------------------------------------------------
 * Function:
 *   void BSTType<T>::insert(const T&, BTNodeType<T>*&)
 *
 * Description:
 *   This is the recursive function of the insert. This function will find
 *   where to insert the item by traversing either the right or the left
 *   branch until a nullptr is met. When the nullptr is met, that nullptr will
 *   be dynamically allocated and the item will be placed there.
 *
 * Preconditions:
 *   The non-recursive function is invoked.
 *
 * Postconditions:
 *   The item is inserted and count is incremented by one.
 * --------------------------------------------------------------------------*/
template<class T> // private
void BSTType<T>::insert(const T& item, BTNodeType<T>*& node)
{
  /* If we have an item to insert, and we already have the given list and
   * another value of 10, this means:
   *
   * Value to insert: 10
   *
   *         [10]    This is the current tree.
   *        /    \
   *      [NP]  [NP]
   *
   * If we want to insert a value of 10, we will have to create an an iterator
   * and then insert the iterator into the tree.  Since 10 is just a duplicate
   * value, we will simply say that it is the parent and then move the test of
   * the tree down by repointing things.
   *
   * Here, prepare the iterator for insertion.
   * -----------------------------------------
   *   [10]
   *         [10] ← Current root (or parent)
   *        /    \
   *      [NP]  [NP]
   *
   *
   * Then we can reroute some pointers
   * ---------------------------------
   *     [10] 
   *    /    \
   *  [NP]  [10] ← Inserted here (for duplicate values insert right)
   *        /  \
   *      [NP][NP]
   *
   * However, if we had a heavily populated list already, things would still be
   * quite similar.
   *
   *   Value to insert: 28
   *
   *               [11]
   *               /  \
   *              /    \
   *             /      \
   *            /        \
   *         [06]       [19]
   *         /  \       /  \
   *        /    \     /    \
   *      [04]  [08] [17]  [43]
   *        \      \       /  \
   *       [05]   [10]   [31][49]
   *
   *   This means that the value 28 needs to be inserted to the left of 31.
   *   With some repoint the pointers. When traversing for insert, we will
   *   eventally get to the point where we are at the node that holds item 31.
   *   Once there, insert 28 to the left of 31 since 28 is less than 31.
   *   
   *   CODE EXAMPLE FOR THIS
   *   ---------------------
   *     if(item == obj->item)
   *       // Do what was described above
   *     else if(item >= obj->item)
   *       insert(item, obj->right;
   *     else if(item <= obj->item)
   *       insert(item, obj->left);
   *     else
   *       // The only option left is nullptr
   *       // So need to allocate memory for it
   *    
   *
   *                                    
   *            [11]                             [11]
   *            /  \                             /  \
   *           /    \                           /    \
   *          /      \                         /      \
   *         /        \                       /        \
   *      [06]       [19]                  [06]       [19]
   *      /  \       /  \                  /  \       /  \
   *     /    \     /    \                /    \     /    \
   *   [04]  [08] [17]  [43]            [04]  [08] [17]  [43]  
   *     \      \       /  \              \      \       /  \
   *    [05]   [10]   [31][49]           [05]   [10]   [31][49]
   *                  /                                /
   *                [NP]       Value inserted here → [28]
   *                 ↑        ----------------------------
   *                 It gets here eventually, and when it does, we
   *                 will allocate memory for it.
   *
   *
   * What if we had a duplicate item needed to be inserted, but it isn't the
   * root node this time?
   *
   *    Item to insert: 43
   *
   *            [11]                             [11]
   *            /  \                             /  \
   *           /    \                           /    \
   *          /      \                         /      \
   *         /        \                       /        \
   *      [06]       [19]      ------>     [06]       [19]
   *      /  \       /  \                  /  \       /  \
   *     /    \     /    \                /    \     /    \
   *   [04]  [08] [17]  [43]            [04]  [08] [17]  [43]
   *     \      \       /  \              \      \       /  \
   *    [05]   [10]   [31][49]           [05]   [10]   [31][49]
   *                                                       /
   *                                                     [43]
   *                          The value is inserted here  ↑↑
   *                            
   * */

  if(node == nullptr)
  {
    try
    {
      // Dynamically allocate
      node = new BTNodeType<T>;

      // Iterator item is set to value of item to inserted.
      node->item = item;

      // Increment count
      count++;
    }
    catch(std::bad_alloc&)
    {
      // Do nothing, just catch.
    }
  }
  else if(item <= node->item)
    insert(item, node->left);
  else if(item >= node->item)
    // insert right
    insert(item, node->right);
}

/* ----------------------------------------------------------------------------
 * Function:
 *   size_t BSTType<T>::size() const
 *
 * Description:
 *   This is the infamous one-liner function, if you exclude the template.
 *   Anyways, it just returns the current count of the list which denotes how
 *   many items there are in the list.
 *
 * Preconditions:
 *   None.
 *
 * Postconditions:
 *   Does not modify anything. Only returns the count of how many items there
 *   are in the tree.
 * --------------------------------------------------------------------------*/
template<class T> size_t BSTType<T>::size() const { return this->count; }

/* ----------------------------------------------------------------------------
 * Function:
 *   void BSTType<T>::copy(BTNodeType<T>&, BTNodeType<T>&)
 *
 * Description:
 *   This is the function that actually be doing the deep copy. First, we copy
 *   the parent node. Then after we copy the parent node, we traverse the left
 *   branches and copy all the left branches through recursion. After
 *   traversing the left through recursion, the function will then traverse the
 *   right branches recursively and copy the right items from the source into
 *   the tree that the source is being copied to.
 *
 * Preconditions:
 *   The first argument is the node on the tree that is going to be dynamically
 *   allocated. The second argument is the source node which contains the item
 *   that is needed and that is going to be copied to the newly allocated node
 *   so that it gets its own copy.
 *
 * Postconditions:
 *   The source tree items are deep copied into another tree.
 * --------------------------------------------------------------------------*/
template<class T>
void BSTType<T>::copy(BTNodeType<T>*& node, BTNodeType<T>* nodeSource)
{
  if(nodeSource != nullptr)
  {
    // Allocate memory for current node
    node = new BTNodeType<T>;
    node->item = nodeSource->item;
    count++;

    // Traverse the left to allocate memory.
    copy(node->left, nodeSource->left);
    
    // After left, traverse right and allocate memory.
    copy(node->right, nodeSource->right);
  }
}

/* ----------------------------------------------------------------------------
 * Function:
 *   void BSTType<T>::destroy(BTNodeType<T>*&)
 *
 * Description:
 *   This will traverse the tree and deallocate all the allocated nodes. The
 *   function does that by traversing the left branches first. After traversing
 *   the left branches, it will then traverse the right branches to deallocate
 *   nodes.
 *
 * Preconditions:
 *   The argument is the node that we first start with. After that, the
 *   function is invoked in a recursive manner such that every node is
 *   deallocated.
 *
 * Postconditions:
 *   All nodes in the tree that are not nullptr (implying that they have not
 *   been allocated) are deallocated.
 * --------------------------------------------------------------------------*/
template<class T> // private
void BSTType<T>::destroy(BTNodeType<T>*& node)
{
  if(node != nullptr)
  {
    destroy(node->left);
    destroy(node->right);
    delete node;
    node = nullptr;
  }
}
  
/* ----------------------------------------------------------------------------
 * Function:
 *   void BSTType<T>::erase(const T&, BTNodeType<T>*&)
 *
 * Description:
 *   This function is a recursive erase function. It will attempt to find an
 *   item and then erase it from the tree. If the item is erased (found) then
 *   it returns true. Otherwise, it returns false.
 *
 * Preconditions:
 *   The argument passed in is the item to be erased from the tree.
 *
 * Postconditions:
 *   If the item is found, the item is erased. Count is decremented by one.
 * --------------------------------------------------------------------------*/
template<class T> // private
void BSTType<T>::erase(const T& item, BTNodeType<T>*& node)
{
  // If not nullptr, we potentially have something to delete
  if(node != nullptr)
  {
    // If it is the item is going to be deleted from the tree...
    if(item == node->item)
    {
      if(node->right == nullptr)
      {
        /* If nothing is on the right of the node when we are going to delete
         * it, then we can just simply remove it. But before simply removing,
         * we have to save its left children. It will look something like this:
         *
         *           [11]
         *           /  \
         *          /    \
         *         /      \
         *        /        \
         *     [06]       [19] ← remove this
         *                /  \
         *               /    \
         *             [17]  [NP] ← nullptr
         *             /
         *           [43]
         *           /  \
         *         [31][49]
         *  
         *  -------------------------------------------------------------------
         *
         *           [11]
         *           /  \
         *          /    \
         *         /      \
         *        /        \
         *     [06]       [NP] ← now we need to let this area become the
         *                       iterator
         *               
         *         ↓ This is the iterator. It is pointing to the 17 node.     
         *        [I]→[17]
         *             /
         *           [43]
         *           /  \
         *         [31][49]
         *  
         *  We set the node that was 19 to the iterator node, and by doing so
         *  the tree now becomes this:
         *
         *           [11]
         *           /  \
         *          /    \
         *         /      \
         *        /        \
         *     [06]       [17]
         *                /
         *              [43]
         *              /  \
         *            [31][49]
         * */
        BTNodeType<T>* iterator = node->left;
        delete node;
        node = iterator;
        count--;
      }
      else if(node->left == nullptr)
      {
        /* If nothing is on the left of the node when we are going to delete
         * it, then we can just simply remove it. But before simply removing,
         * we have to save its right children. It will look something like this:
         *
         *           [11]
         *           /  \
         *          /    \
         *         /      \
         *        /        \
         *     [06]       [19] ← remove this
         *                /  \
         *               /    \
         *     nullptr→[NP]  [30]
         *                   /  \
         *                 [25][40]
         *  
         *  We create an iterator so we can access the left branches later. The
         *  reason why this is done is because after removing 19, the node
         *  which contains 17 is going to be put into the place of 19.
         *
         *           [11]
         *           /  \
         *          /    \
         *         /      \
         *        /        \
         *     [06]       [NP] ← now we need to let this area become the
         *                       iterator
         *
         *                 Iterator
         *                 ↓
         *                [I]→[30]
         *                    /  \
         *                  [25][40]
         *  
         *  We set the node that was 19 to the iterator node, and by doing so
         *  the tree now becomes this:
         *
         *           [11]
         *           /  \
         *          /    \
         *         /      \
         *        /        \
         *     [06]       [30]
         *                /  \
         *              [25][40]
         * */
        BTNodeType<T>* iterator = node->right;
        delete node;
        node = iterator;
        count--;
      }
      else
      {
        /* If the function was able to find the item to erase, but the node
         * that is going to be erased already has two children, we will assign
         * the node's item to the predecessor.
         *
         *             [06]
         *             /  \
         *            /    \
         *          [01]  [20] ← erasing this, but it already has two children,
         *               /    \  so we need to get the predecessor, which is
         *              /      \ the value 19.
         *            [15]    [30]
         *            /  \    /  \
         *          [13][19][25][50]
         *
         * While getting the predecessor, we will also manipulate items in the
         * tree such that everything is worked out neatly.
         *
         *             [06]
         *             /  \
         *            /    \
         *          [01]  [19]
         *               /    \
         *              /      \
         *            [15]    [30]
         *            /  \    /  \
         *          [13][19][25][50]
         *                ↑
         *                Call the erase function on this node.
         *
         * Above, we copied the value of the predecessor into the node, and
         * everything is where it should be. The only thing left to do remove
         * the predecessor now, in which the erase function is called again to
         * remove the 19 from the bottom.
         * */
        node->item = predecessor(node->left);
        erase(node->item, node->left);
      }
    }
    else if(item < node->item)
      erase(item, node->left);
    else
      erase(item, node->right);
  }
}

/* ----------------------------------------------------------------------------
 * Function:
 *   void BSTType<T>::inorder(std::ostream&, BTNodeType<T>*) const
 *
 * Description:
 *   This is the inorder traversal. It will print the tree to an output stream
 *   by doing an inorder traversal, where the left node is considered first,
 *   the root node is considered second, and the right rood is consdierd third.
 *   For example:
 *
 *               [11]
 *               /  \
 *              /    \
 *             /      \
 *            /        \
 *         [06]       [19]
 *         /  \       /  \
 *        /    \     /    \
 *      [04]  [08] [17]  [43]
 *        \      \       /  \
 *       [05]   [10]   [31][49]
 * 
 * The tree will be printed like this:
 *   4, 5, 6, 8, 10, 11, 17, 19, 31, 43, 49
 *
 * Preconditions:
 *   The first parameter is an output source. For example (since this is C++),
 *   the output source could be std::cout, or std::ofstream. The second
 *   argument is the current node the traveral is on. This node's current item
 *   if fed into the output stream object.
 *
 * Postconditions:
 *   Does not modify anything.
 * --------------------------------------------------------------------------*/
template<class T> // private
void BSTType<T>::inorder(std::ostream& os, BTNodeType<T>* node) const
{
  if(node != nullptr)
  {
    inorder(os, node->left);
    os << node->item << " ";
    inorder(os, node->right);
  }
}

/* ----------------------------------------------------------------------------
 * Function:
 *   void BSTType<T>::postorder(std::ostream&, BTNodeType<T>*) const
 *
 * Description:
 *   This will do a post order traversal. Everything is similar to the inorder
 *   traversal, but the output is just different. In postorder, the left node
 *   is printed, the right node, and then the parent node is printed. Take the
 *   tree below for example:
 *
 *               [11]
 *               /  \
 *              /    \
 *             /      \
 *            /        \
 *         [06]       [19]
 *         /  \       /  \
 *        /    \     /    \
 *      [04]  [08] [17]  [43]
 *        \      \       /  \
 *       [05]   [10]   [31][49]
 *
 * The tree will be printed like this:
 *   5 4 10 8 6 17 31 49 43 19 11
 *
 * Preconditions:
 *
 * Postconditions:
 * --------------------------------------------------------------------------*/
template<class T> // private
void BSTType<T>::postorder(std::ostream& os, BTNodeType<T>* node) const
{
  if(node != nullptr)
  {
    postorder(os, node->left);
    postorder(os, node->right);
    os << node->item << " ";
  }
}

/* ----------------------------------------------------------------------------
 * Function:
 *   const T& BSTType<T>::predecessor(BTNodeType<T>*)
 *
 * Description:
 *   This function will get the furthest right node from the left branch.
 *
 * Preconditions:
 *   The erase function is invoked and a node that is going to be erased
 *   already has two children. This function will swap that node and the
 *   rightmost node value with that node that is going to be "erased".
 *
 * Postconditions:
 *   Returns the rightmost node of a left branch.
 * --------------------------------------------------------------------------*/
template<class T>
const T& BSTType<T>::predecessor(BTNodeType<T>* node)
{
  while(node->right != nullptr)
    node = node->right;
  return node->item;
}

/* ----------------------------------------------------------------------------
 * Function:
 *   void BSTType<T>::preorder(std::ostream&, BTNodeType<T>*) const
 *
 * Description:
 *   This is the preorder traversal. It will print the tree to an output stream
 *   by doing an preorder traversal, where the root node is considered first,
 *   then the left, then the right.
 *   For example:
 *
 *               [11]
 *               /  \
 *              /    \
 *             /      \
 *            /        \
 *         [06]       [19]
 *         /  \       /  \
 *        /    \     /    \
 *      [04]  [08] [17]  [43]
 *        \      \       /  \
 *       [05]   [10]   [31][49]
 *
 * The tree is printed in this manner:
 *   11, 6, 4, 5, 8, 10, 19, 17, 43, 31, 49
 *
 * Preconditions:
 *   The first argument that is an object that belongs to an output stream. The
 *   second argument is the current node that it is on. This node's item is fed
 *   into the output stream's object.
 *
 * Postconditions:
 * --------------------------------------------------------------------------*/
template<class T>
void BSTType<T>::preorder(std::ostream& os, BTNodeType<T>* node) const
{
  if(node!= nullptr)
  {
    os << node->item << " ";
    preorder(os, node->left);
    preorder(os, node->right);
  }
}

/* ----------------------------------------------------------------------------
 * Function:
 *  void BSTType<T>::traverse(std::ostream&, TravType) const
 *
 * Description:
 *   This function traverses the tree and outputs whatever is on the
 *   tree depending on the traversal type.
 *
 * Preconditions:
 *   An object of the BSTType class is the on the right hand side of
 *   the extraction operator.
 *
 * Postconditions:
 *   Does not modify anything.
 * --------------------------------------------------------------------------*/
template<class T>
void BSTType<T>::traverse(std::ostream& os, TravType trav) const
{
  switch(trav)
  {
    // If given a preorder travel enum, do a preorder traversal.
    case PRE:
    {
      preorder(os, root);
      break;
    }
    // If given a inorder travel enum, do a inorder traversal.
    case IN:
    {
      inorder(os, root);
      break;
    }
    // If given a postorder travel enum, do a postorder traversal.
    case POST:
    {
      postorder(os, root);
    }
  }
}
#endif
