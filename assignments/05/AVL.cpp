////////////////////////////////////////////////////////////////////////////////
// Name: Jim Moua
// Program 05
// Description:
// Special Processing Requirements: Requires 
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////
// Libraries to include
//////////////////////////////
#include <iostream>
#include <limits>

////////////////////////////////////////////////////////////////////////////////
// MISC: I need a function for clearing the input stream if the input is valid
//       and causes the program to spaz out.
////////////////////////////////////////////////////////////////////////////////
namespace jm {
  template<typename T>
  static void input(T& foo) {
    std::cin >> foo;
    if(!std::cin) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else std::cin.clear();
  }
  void getline(std::string& foo) {
    std::getline(std::cin, foo);
  }
}
 
////////////////////////////////////////////////////////////////////////////////
// Struct: avl_node
//
// Description:
// This is essentially just a node within a tree. While declaring the avl_node
// structure, we also declare an pointer avl_node called root.
////////////////////////////////////////////////////////////////////////////////
struct avl_node {
  int data;
  avl_node *left;
  avl_node *right;
}*root;
 
////////////////////////////////////////////////////////////////////////////////
// Class: avlTree
// Description:
////////////////////////////////////////////////////////////////////////////////
class avlTree {
  public:
    int height(avl_node*);
    int diff(avl_node*);
    avl_node* rr_rotation(avl_node*);
    avl_node* ll_rotation(avl_node*);
    avl_node* lr_rotation(avl_node*);
    avl_node* rl_rotation(avl_node*);
    avl_node* balance(avl_node*);
    avl_node* insert(avl_node*, int);
    void display(avl_node*, int);
    void inorder(avl_node*);
    void preorder(avl_node*);
    void postorder(avl_node*);
    avlTree() {
      root = nullptr;
    }
};
 
////////////////////////////////////////////////////////////////////////////////
// Function: main()
//
// Description:
// It is the main function - every c++ program needs one! This main function
// will contain the menu of the program as well.
////////////////////////////////////////////////////////////////////////////////
int main() {

  // choice → The option that users choose in the menu
  //   item → If the chosen menu option is to insert some node into the list,
  //          then item represents the data of that node.
  int choice, item;

  // Declare an object of avlTree
  avlTree avl;

  // While inMenu → infinite loop the menu
  bool inMenu = true;
  while(inMenu) {
    // Print a menu
    std::cout << "\n---------------------\n";
    std::cout << "AVL Tree Implementation";
    std::cout << "\n---------------------\n";
    std::cout << "1.Insert Element into the tree\n";
    std::cout << "2.Display Balanced AVL Tree\n";
    std::cout << "3.InOrder traversal\n";
    std::cout << "4.PreOrder traversal\n";
    std::cout << "5.PostOrder traversal\n";
    std::cout << "6.Exit\n";
    std::cout << "Enter your Choice: ";

    // Get the input for choice
    jm::input(choice);

    // Switch choice → branch to corresponding choice options
    switch(choice) {
      // 1 = Insert a value into the AVL tree
      case 1:
      {
        std::cout<<"Enter value to be inserted: ";
        jm::input(item);
        root = avl.insert(root, item);
        break;
      }
      // 2 = Print the tree
      case 2:
      {
        if (root == nullptr) {
          std::cout << "Tree is Empty\n";
          continue;
        }
        std::cout << "Balanced AVL Tree:\n";
        avl.display(root, 1);
        break;
      }
      // 3 = Print inorder traversal
      case 3:
      {
        std::cout << "Inorder Traversal:\n";
        avl.inorder(root);
        std::cout << std::endl;
        break;
      }
      // 4 = Print preorder traversal
      case 4:
      {
        std::cout << "Preorder Traversal:\n";
        avl.preorder(root);
        std::cout << std::endl;
        break;
      }
      // 5 = Print postorder traversal
      case 5:
      {
        std::cout << "Postorder Traversal:\n";
        avl.postorder(root);    
        std::cout << std::endl;
        break;
      }
      // 6 = exit program
      case 6:
      {
        // Break out of the main menu (infinite loop) and close the program.
        inMenu = false;
        break;
      }
      default:
      {
        std::cout << "Wrong Choice" << std::endl;
      }
    }
  }
  return 0;
}
 
/*
 * Height of AVL Tree
 */
////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree::height(avl_node* tmp)
//
// Description:
// Computes the height of the tree via recursion. This means every subtree's
// height will be calculated.
// 
// Preconditions:
// None
//
// Postconditions:
// Returns the height of tree/subtree.
////////////////////////////////////////////////////////////////////////////////
int avlTree::height(avl_node* temp) {
  int h = 0;
  if (temp != nullptr) {
    int l_height = height(temp->left);
    int r_height = height(temp->right);
    int max_height = std::max(l_height, r_height);
    h = max_height + 1;
  }
  return h;
}
 
////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree::diff(avl_node* tmp)
//
// Preconditions:
// None
//
// Postconditions:
// None
////////////////////////////////////////////////////////////////////////////////
int avlTree::diff(avl_node* temp) {
  int l_height = height(temp->left);
  int r_height = height(temp->right);
  return (l_height-r_height);
}
 
/*
 * Right- Right Rotation
 */
////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree::rr_rotation(avl_node* parent)
//
// Description:
// Performs a right rotation about the parent node. The parent node is never
// modified. The function returns a pointer called temp.
//
// temp points to the parent's right child, and temp's left child points to the
// parent.
//
//       [P] [T] → [R]
//       / \ /
//     [L] [P]
//
////////////////////////////////////////////////////////////////////////////////
//
//     [T] → [R]
//     /
//    [P]
//
////////////////////////////////////////////////////////////////////////////////
//
//     [T] → [R]
//     /
//    [P]
//
////////////////////////////////////////////////////////////////////////////////
//
//     [R] ← essentially, we are returning something like this (parent's right)
//     /
//    [P]
//
////////////////////////////////////////////////////////////////////////////////
avl_node* avlTree::rr_rotation(avl_node *parent) {
  // Create a pointer temp
  //       [P]
  //         \
  //         [R]  [T]
  //           \
  //           [q]
  avl_node* temp;

  // Assign temp to the parent's right child
  //       [P]
  //         \
  //         [R] ← [T]
  //           \
  //          [q]
  temp = parent->right;

  // Assign parent's right child to temp's left child
  //       [P]  [T] → [R]
  //       / \  /
  //     [L] [TL]
  parent->right = temp->left;

  // Assign temp left to parent
  //       [P] [T] → [R]
  //       / \ /
  //     [L] [P]
  //
  //       [P] [R]
  //       / \ /
  //     [L] [P]
  temp->left = parent;

  // Returns temp
  // temp is current pointing to the parent's right child
  // temp's left child is pointing to parent node
  return temp;
}

////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree::ll_rotation(avl_node* parent)
//
// Description:
// Performs a left-left rotation.
////////////////////////////////////////////////////////////////////////////////
avl_node *avlTree::ll_rotation(avl_node* parent) {

  // Create an avl_node pointer called temp
  //       [P]
  //       / \
  // [T] [L] [R]
  //     / \
  //   [l] [r]
  avl_node *temp;

  // temp points to the parent's left child
  //       [P]
  //       / \
  // [T]→[L] [R]
  //     / \
  //   [l] [r]
  temp = parent->left;

  // parent's left child points to temp's right child
  //       [P]
  //       / \
  // [T]→[L] [R]
  //     / \
  //   [l] [r]
  //
  //       [P]
  //       / \
  //     [r] [R]    temp is pointing to left, so temp->right = Left->right
  //     /
  //   [l]
  parent->left = temp->right;

  //       [P]
  //       / \
  //     [r] [R]    temp is pointing to left, so temp->right = Left->right
  //     /
  //   [l]
  temp->right = parent;
  return temp;
}
 
/*
 * Left - Right Rotation
 */
avl_node *avlTree::lr_rotation(avl_node *parent) {
  avl_node *temp;
  temp = parent->left;
  parent->left = rr_rotation (temp);
  return ll_rotation (parent);
}
 
/*
 * Right- Left Rotation
 */
avl_node *avlTree::rl_rotation(avl_node *parent) {
  avl_node *temp;
  temp = parent->right;
  parent->right = ll_rotation (temp);
  return rr_rotation (parent);
}
 
/*
 * Balancing AVL Tree
 */
avl_node *avlTree::balance(avl_node *temp) {
  int bal_factor = diff (temp);
  if (bal_factor > 1) {
    if (diff (temp->left) > 0)
      temp = ll_rotation (temp);
    else
      temp = lr_rotation (temp);
  }
  else if (bal_factor < -1) {
    if (diff (temp->right) > 0)
      temp = rl_rotation (temp);
    else
      temp = rr_rotation (temp);
  }
  return temp;
}
 
/*
 * Insert Element into the tree
 */
avl_node *avlTree::insert(avl_node *root, int value) {
  if (root == nullptr) {
    root = new avl_node;
    root->data = value;
    root->left = nullptr;
    root->right = nullptr;
    return root;
  }
  else if (value < root->data) {
    root->left = insert(root->left, value);
    root = balance (root);
  }
  else if (value >= root->data) {
    root->right = insert(root->right, value);
    root = balance (root);
  }
  return root;
}
 
/*
 * Display AVL Tree
 */
void avlTree::display(avl_node *ptr, int level)
{
  int i;
  if (ptr!=nullptr) {
    display(ptr->right, level+1);
    printf("\n");
    if (ptr == root) {
      std::cout<<"Root -> ";
    }
    for (i = 0; i < level && ptr != root; i++) {
      std::cout<<"        ";
    }
    std::cout << ptr->data;
    display(ptr->left, level+1);
  }
}
 
/*
 * Inorder Traversal of AVL Tree
 */
void avlTree::inorder(avl_node *tree)
{
  if(tree == nullptr) {
    return;
  }
  inorder (tree->left);
  std::cout<<tree->data<<"  ";
  inorder (tree->right);
}

/*
 * Preorder Traversal of AVL Tree
 */
void avlTree::preorder(avl_node *tree) {
  if (tree == nullptr) {
    return;
  }
  std::cout << tree->data << "  ";
  preorder(tree->left);
  preorder(tree->right);
}
 
/*
 * Postorder Traversal of AVL Tree
 */
void avlTree::postorder(avl_node *tree) {
  if (tree == nullptr) {
    return;
  }
  postorder(tree->left);
  postorder(tree->right);
  std::cout << tree->data << "  ";
}
