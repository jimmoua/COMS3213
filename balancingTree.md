# Balancing Trees

Balacing a tree can be helpful because it can make our data structure much more
efficient in terms of searching/modifying.

A binary tree is **height balanced** if the difference in height of subtrees of
any node in the tree is zero or one. It's **perfectly balanced** if all nodes
are one of two levels different from each other.

| Height | Nodes at One Level | Nodes at All Levels
| :----: | :----------------: | :-----------------:
| 1      | $2^0$              | $1=2^1-1$
| 2      | $2^1=2$            | $3=2^2-1$
| 3      | $2^2=4$            | $7=2^3-1$
| 4      | $2^3=8$            | $15=2^4-1$
| h      | $2^h-1$            | $n=2^h -1$

```c++
// Example of balance function that will balance an array
template<typename T>
void BST<T>::balance(T data[], int first, int last) {
  if(first <= last) {
    int middle = (first = last)/2;
    insert(data[middle]);
    balance(data, first, middle-1);
    balance(data, middle+1, last);
  }
}
```

## Day Stout Warren Algorithm

The DSW algorithm is an algorithm for balancing trees. This algorithm
**utilizes rotation in order to do this**. There are two types of rotation:
**left and right** (symmetrical to one another).

```
// Right rotation pseudocode
//   Gr  = Grandparent
//   Par = Parent
//   Ch  = Child
rotateRight(Gr, Par, Ch) {
    if Par is not root of tree {
      Gr becomes Ch's parent;
    }
    Right subtree of Ch becomes left subtree of Ch's parent Par;
    Node Ch acquires Par as its right child;
}
```

This will transform the binary tree into a **linked list-like tree called a
backbone or vine**. After this, the tree is then transformed in a series of
passes (via recurrsion or iteration) into a perfectly balanced tree by
repeatedly rotating every second node of the backbone about its parent.

### DSW Steps

In the **first step**, we create a **backbone or vine**
```c++
createBackBone(root) {
  tmp = root;
  while(tmp!=nullptr) {
    if(tmp.hasLeftChild()) {
      // Rotate the left child about tmp
      //   → left child becomes parent of tmp
      //           ↑
      // Then set tmp = as a child of that left node that became a parent
    }
    else {
      // set tmp = to its right child
    }
  }
}
```

Then we can create the perfectly balanced tree:
```
createPerfectTree() {
  n = numberOfNodes;'
  m = 2^{lg(n+1)}-1; // wtf does this mean?
  make n-m rotations starting from top of backbone;
  while(m > 1) {
    m = m/2;
    make m rotations starting from the top of backbone;
  }
}
```

## AVL Trees

A binary tree is an **AVL** tree that is empty or satisfies the following two:
1. The heights of the left and rigth subtrees differ by **at most** 1
2. The left and right subtrees are AVL trees.
