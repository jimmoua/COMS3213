////////////////////////////////////////////////////////////////////////////////
// Name: Jim Moua
//
// Program 05
//
// Description:
//   This program is a play with binary search trees - but not just any binary
//   search tree. It is an AVL tree, a type of binary search tree in which the
//   height of the left or right subtrees differ by at most one.
//
// Special Processing Requirements:
//   Program requires C++11 to compile, since nullptrs are being used instead
//   of the normal NULL for pointers.
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////
// Standard libraries include
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
//
// Description:
// The avlTree class is the class in which instantiated objects will represent
// the AVL tree.
////////////////////////////////////////////////////////////////////////////////
class avlTree {
  private:
    int height(avl_node*);
    int diff(avl_node*);
    avl_node* rr_rotation(avl_node*);
    avl_node* ll_rotation(avl_node*);
    avl_node* lr_rotation(avl_node*);
    avl_node* rl_rotation(avl_node*);
    avl_node* balance(avl_node*);
  public:
    void display(avl_node*, int);
    void inorder(avl_node*);
    void preorder(avl_node*);
    void postorder(avl_node*);
    avl_node* insert(avl_node*, int);
    // Default ctor
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
 
////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree::height(avl_node* tmp)
//
// Description:
// Computes the height of a subtree via recursion.
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
// Description:
// Returns the difference in height of the left subtree and the right subtree.
//
// Preconditions:
// None
//
// Postconditions:
// Returns an integer - one that is the difference in heights of left and right
// subtrees.
////////////////////////////////////////////////////////////////////////////////
int avlTree::diff(avl_node* temp) {
  int l_height = height(temp->left);
  int r_height = height(temp->right);
  return (l_height-r_height);
}
 
////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree::rr_rotation(avl_node* parent)
//
// Description:
// Performs a right rotation about the parent node. The parent node is never
// modified. The function returns a pointer called temp.
//
// Preconditions:
// None.
//
// Postconditions:
// Returns a node called temp as a parent node after right-right rotation has
// been performed.
////////////////////////////////////////////////////////////////////////////////
avl_node* avlTree::rr_rotation(avl_node* parent) {
  // Create an avl_node claled temp
  avl_node* temp;

  // Temp points to parent's right child
  temp = parent->right;

  // Parent's right child points to temp's left child.
  parent->right = temp->left;

  // Temp's left child points to parent
  temp->left = parent;

  // Returns the node temp, which acts as the node to a right-rotated subtree.
  return temp;
}

////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree::ll_rotation(avl_node* parent)
//
// Description:
// Performs a left-left rotation.
//
// Preconditions:
// None.
//
// Postconditions:
// Returns a node called temp as a parent node after left-left rotation has
// been applied.
////////////////////////////////////////////////////////////////////////////////
avl_node *avlTree::ll_rotation(avl_node* parent) {

  // Create an avl_node called temp
  avl_node *temp;

  // temp points to parent's left child
  temp = parent->left;

  // parent's left child now points to temp's right child
  parent->left = temp->right;

  // temp's right child points to parent
  temp->right = parent;

  // return the temp node, which is essentially the left rotation about the
  // parent.
  return temp;

}
 
////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree::lr_rotation(avl_node* parent)
//
// Description:
// Performs a left-right rotation on a subtree about the parent node.
//
// Preconditions:
// None.
//
// Postconditions:
// Returns temp node after performing left-right rotation about the parent node.
////////////////////////////////////////////////////////////////////////////////
avl_node *avlTree::lr_rotation(avl_node* parent) {

  // Create an avl_node called temp
  avl_node* temp;

  // temp points to the parent's left child.
  temp = parent->left;

  // perform a right-right rotation on the temp node, and let parent's left
  // child point to it
  parent->left = rr_rotation(temp);

  // Perform a left-left rotation on the parent node, and then return it.
  return ll_rotation(parent);

}
 
////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree::rl_rotation(avl_node* parent)
//
// Description:
// Performs a right-left rotation on a subtree about the parent node.
//
// Postconditions:
//
// Preconditions:
// Returns a the parent node, which has been rotated via right-left rotation.
////////////////////////////////////////////////////////////////////////////////
avl_node* avlTree::rl_rotation(avl_node* parent) {

  // Create an avl_node called temp
  avl_node* temp;

  // temp points to the parent's right child
  temp = parent->right;

  // Perform a left-left rotation on the node temp, and then set parent's right
  // child to point to it.
  parent->right = ll_rotation(temp);

  // Perform a right-right rotation on the node parent, and return it.
  return rr_rotation(parent);

}
 
////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree::balance(avl_node* temp)
//
// Description:
// Balances a subtree.
//
// Postconditions:
// None.
//
// Preconditions:
// Returns a node as the parent node after balancing the (sub)tree.
////////////////////////////////////////////////////////////////////////////////
avl_node* avlTree::balance(avl_node* temp) {

  // Get the balance factor tree/subtree
  int bal_factor = diff (temp);

  // If the balance factor is greater than one, we need to balance the tree
  if (bal_factor > 1) {
    // If the difference in height on the left is greater than 0, perform
    // left-left rotation. Otherwise, perform a left-right rotation.
    if (diff(temp->left) > 0) {
      temp = ll_rotation(temp);
    }
    else {
      temp = lr_rotation(temp);
    }
  }
  // The same applies here, that is, is the balance factor is less than -1, we
  // need to balance the tree
  else if (bal_factor < -1) {
    if (diff(temp->right) > 0) {
      temp = rl_rotation (temp);
    }
    else {
      temp = rr_rotation (temp);
    }
  }
  
  // Return node after performing rotations to balance it.
  return temp;

}
 
////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree::insert(avlnode* root, int value)
//
// Description:
// Inserts an avl_node with the provided value
//
// Preconditions:
// None.
//
// Postconditions:
// Returns root node after performing an insert.
////////////////////////////////////////////////////////////////////////////////
avl_node *avlTree::insert(avl_node* root, int value) {
  // Keep traversing the tree until we've hit a nullptr. Once we've gotten to a
  // node that is nullptr, we will allocate space for it, and assign a value to
  // the node.
  if (root == nullptr) {
    root = new avl_node;
    root->data = value;
    root->left = nullptr;
    root->right = nullptr;
    return root;
  }
  // Otherwise, perform recursive binary search to determine where to insert
  // the node according to its value.
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
 
////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree:display(avlnode* ptr, int level)
//
// Description:
// Prints the AVL tree.
//
// Preconditions:
// None.
//
// Postconditions:
// Traverserves the tree and displays in a tree-like format (but sideways).
////////////////////////////////////////////////////////////////////////////////
void avlTree::display(avl_node* ptr, int level)
{
  // If the tree isn't empty, print the tree
  if (ptr!=nullptr) {
    display(ptr->right, level+1);
    printf("\n");
    if (ptr == root) {
      std::cout<<"Root -> ";
    }
    for (int i = 0; i < level && ptr != root; i++) {
      std::cout<<"        ";
    }
    std::cout << ptr->data;
    display(ptr->left, level+1);
  }
}
 
////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree:inorder(avl_node* tree)
//
// Description:
// Perform an inorder traversal on the tree, and print the values in the nodes
// while doing inorder traversal.
//
// Preconditions:
// None.
//
// Postconditions:
// Performs inorder traversal on a tree.
////////////////////////////////////////////////////////////////////////////////
void avlTree::inorder(avl_node* tree)
{
  if(tree == nullptr) {
    return;
  }
  inorder(tree->left);
  std::cout << tree->data << "  ";
  inorder(tree->right);
}

////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree:preorder(avl_node* tree)
//
// Description:
// Perform an preorder traversal on the tree, and print the values in the nodes
// while doing preorder traversal.
//
// Preconditions:
// None.
//
// Postconditions:
// Perfoms preorder traversal on a tree.
////////////////////////////////////////////////////////////////////////////////
void avlTree::preorder(avl_node* tree) {
  if (tree == nullptr) {
    return;
  }
  std::cout << tree->data << "  ";
  preorder(tree->left);
  preorder(tree->right);
}
 
////////////////////////////////////////////////////////////////////////////////
// Function:
// avlTree:postorder(avl_node* tree)
//
// Description:
// Perform an postorder traversal on the tree, and print the values in the
// nodes while doing postorder traversal.
//
// Preconditions:
// None.
//
// Postconditions:
// Performs postorder traversal on a tree.
////////////////////////////////////////////////////////////////////////////////
void avlTree::postorder(avl_node* tree) {
  if (tree == nullptr) {
    return;
  }
  postorder(tree->left);
  postorder(tree->right);
  std::cout << tree->data << "  ";
}
