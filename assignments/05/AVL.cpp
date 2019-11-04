/*
 * C++ program to Implement AVL Tree
 */
#include <iostream>
#include <limits>
 
/*
 * Node Declaration
 */
struct avl_node {
  int data;
  struct avl_node *left;
  struct avl_node *right;
}*root;
 
/*
 * Class Declaration
 */
class avlTree {
  public:
    int height(avl_node *);
    int diff(avl_node *);
    avl_node *rr_rotation(avl_node *);
    avl_node *ll_rotation(avl_node *);
    avl_node *lr_rotation(avl_node *);
    avl_node *rl_rotation(avl_node *);
    avl_node* balance(avl_node *);
    avl_node* insert(avl_node *, int );
    void display(avl_node *, int);
    void inorder(avl_node *);
    void preorder(avl_node *);
    void postorder(avl_node *);
    avlTree() {
      root = nullptr;
    }
};
 
/*
 * Main Contains Menu
 */
int main() {
  int choice, item;
  avlTree avl;
  while(true) {
    std::cout<<"\n---------------------"<<std::endl;
    std::cout<<"AVL Tree Implementation"<<std::endl;
    std::cout<<"\n---------------------"<<std::endl;
    std::cout<<"1.Insert Element into the tree"<<std::endl;
    std::cout<<"2.Display Balanced AVL Tree"<<std::endl;
    std::cout<<"3.InOrder traversal"<<std::endl;
    std::cout<<"4.PreOrder traversal"<<std::endl;
    std::cout<<"5.PostOrder traversal"<<std::endl;
    std::cout<<"6.Exit"<<std::endl;
    std::cout<<"Enter your Choice: ";
    std::cin>>choice;
    // For clearing bad input bit stream
    if(!std::cin) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    }
    switch(choice) {
      case 1:
        std::cout<<"Enter value to be inserted: ";
        std::cin>>item;
        root = avl.insert(root, item);
        break;
      case 2:
        if (root == nullptr) {
          std::cout<<"Tree is Empty"<<std::endl;
          continue;
        }
        std::cout<<"Balanced AVL Tree:"<<std::endl;
        avl.display(root, 1);
        break;
      case 3:
        std::cout<<"Inorder Traversal:"<<std::endl;
        avl.inorder(root);
        std::cout<<std::endl;
        break;
      case 4:
        std::cout<<"Preorder Traversal:"<<std::endl;
        avl.preorder(root);
        std::cout<<std::endl;
        break;
      case 5:
        std::cout<<"Postorder Traversal:"<<std::endl;
        avl.postorder(root);    
        std::cout<<std::endl;
        break;
      case 6:
        exit(1);    
        break;
      default:
        std::cout<<"Wrong Choice"<<std::endl;
    }
  }
  return 0;
}
 
/*
 * Height of AVL Tree
 */
int avlTree::height(avl_node *temp) {
  int h = 0;
  if (temp != nullptr) {
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int max_height = std::max(l_height, r_height);
    h = max_height + 1;
  }
  return h;
}
 
/*
 * Height Difference 
 */
int avlTree::diff(avl_node *temp) {
  int l_height = height (temp->left);
  int r_height = height (temp->right);
  int b_factor= l_height - r_height;
  return b_factor;
}
 
/*
 * Right- Right Rotation
 */
avl_node *avlTree::rr_rotation(avl_node *parent) {
  avl_node *temp;
  temp = parent->right;
  parent->right = temp->left;
  temp->left = parent;
  return temp;
}
/*
 * Left- Left Rotation
 */
avl_node *avlTree::ll_rotation(avl_node *parent) {
  avl_node *temp;
  temp = parent->left;
  parent->left = temp->right;
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
    display(ptr->right, level + 1);
    printf("\n");
    if (ptr == root) {
      std::cout<<"Root -> ";
    }
    for (i = 0; i < level && ptr != root; i++) {
      std::cout<<"        ";
    }
    std::cout<<ptr->data;
    display(ptr->left, level + 1);
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
  std::cout<<tree->data<<"  ";
  preorder (tree->left);
  preorder (tree->right);
}
 
/*
 * Postorder Traversal of AVL Tree
 */
void avlTree::postorder(avl_node *tree) {
  if (tree == nullptr) {
    return;
  }
  postorder ( tree ->left );
  postorder ( tree ->right );
  std::cout<<tree->data<<"  ";
}
