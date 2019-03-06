#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
  bool red;
  Node *parent;

  public:
  Node(int d, Node *p) {
    data = d;
    parent = p;
    red = true;
  }
};
void swapColor(bool &a, bool &b)
{
    bool tmp_color = a;
    a = b;
    b = tmp_color;
}

bool isRed(Node *curr) {
  if (curr)
    return curr->red;
  return false;
}

class RedBlackTree {
 private:
  Node *root;

 private:
    Node *rotateLeft(Node *curr)
    {
      Node *temp = curr->right;
      curr->right = temp->left;
      temp->left = curr;
      return temp;
    }

    Node *rotateRight(Node *curr)
    {
      Node *temp = curr->left;
      curr->left = temp->right;
      temp->right = curr;
      return temp;
    }

    bool look(Node *root, int target) {
      if (root == NULL)
        return false;
      if (root->data == target)
        return true;
      if (root->data < target)
        return look(root->right, target);
      else
        return look(root->left, target);
    }

    Node* Min(Node *root){
    if (root == NULL)
        return NULL;
    else if (root ->left)
        return Min(root->left);
    return root;
    }

  // think about return type
  Node* fix(Node *curr)
  {
    if (!isRed(curr))
      return curr;
    if (curr == root)
    {
      curr->red = false;
      return curr;
    }
    if (!isRed(curr->parent))
      return curr;
    Node *parent = curr->parent;
    Node *gParent = parent->parent;
    Node *uncle;
    if (gParent->left == parent)
      uncle = gParent->right;
    else // gParent->right == parent
      uncle = gParent->left;
    //Case 1: The uncle of parent is also red, only need to recolor
    if (isRed(uncle))
    {
        gParent->parent->red = true;
        gParent->red = false;
        uncle->parent->red = false;
        parent = gParent->parent;
        fix(gParent);
    }
     else
     {
      if (gParent->left == parent)
      { // Case 2: parent is right child of its parent, left rotate
        if (parent->right == curr)
        {
            rotateLeft(root);
            parent = gParent;
            gParent = parent->parent;
        }
        // Case 3: Parent is left child of its parent, right rotate
        rotateRight(root);
        swapColor(gParent->red, gParent->parent->red);
        parent = gParent;
      }
      else
      { // gParent->right == parent // right something case
        if (parent->left == curr)
        {
            // Case 4: parent is left child of its parent, right rotate
            rotateRight(root);
            parent = gParent;
            gParent = parent->parent;
        }
        // Case 5: parent is right child of its parent, left rotate
        rotateLeft(root);
        swapColor(gParent->red, gParent->parent->red);
        parent = gParent;
      }
    }
    curr->red = false;
    return(curr);
  }

  Node *insert(Node *root, Node *parent, bool left, int data) {
    if (!root)
    {
      Node *n = new Node(data, parent);
      if (left)
        parent->left = n;
      else
        parent->right = n;
      fix(n);
      return n;
    }
    if (root->data > data) {
      insert(root->left, root, true, data);
    }
    else {
      insert(root->right, root, false, data);
    }
    return root;
  }

    void level(Node *root) {
      auto q = queue<Node *>();
      q.push(root);
      while(!q.empty()) {
        Node *temp = q.front();
        q.pop();
        cout << temp->data << "("<< 0 << ") ";
        if (temp->left)
          q.push(temp->left);
        if (temp->right)
          q.push(temp->right);
        }
    }

    Node *rem(Node *root, int target) {
        Node* t;
        if(root == NULL)
            return NULL;
        else if (root -> data > target)
        {
            root->left = rem(root -> left, target);
        }
        else if (root -> data < target)
        {
            root -> right = rem(root -> right, target);
        }
        else if (root -> right && root -> left)
        {
            t = Min(root->right);
            root->data = t->data;
            root->right = rem(root->right, root->data);
        }
        else {
            t = root;
            if(root->left == NULL)
                root = root->right;
            else if (root-> right == NULL)
                root = root->left;
            delete t;
        }
        if(root == NULL)
            return NULL;
          // Use same BST logic to find data and delete node
          // Check balance of root
          // If absolute value of balance is > 1:
          //// Case 1: If balance is positive
          //// Check balance of root->left
          ////// If negative, rotate root->left to the left; set root->left to result
          //// Rotate root right; set root to result
          //// Case 2: If balance is negative
          //// Check balance of root->right
          ////// If positive, rotate root->right to the right; set root->right to result
          //// Rotate root left; set root to result
          //// Update height of root to be 1 + max(left, right)
        return NULL;
    }


 public:
    RedBlackTree()
    {
        root = NULL;
    }

    bool lookup(int target) {
        return look(root, target);
    }

    void insert(int data) {
        root = insert(root, nullptr, false, data);
    }

    void levelOrder(){
        level(root);
    }

    void remove(int target){
        //root = rem(root, target);
    }

};

int main() {

    //initialze variables
    RedBlackTree n;
    int dat, m;
    string x;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> x;
        if (x == "lookup")
        {
            cin >> dat;
            cout << n.lookup(dat) << endl;
        }
        else if (x == "insert")
        {
            cin >> dat;
            n.insert(dat);
        }
        else if (x == "delete")
        {
            cin >> dat;
            n.remove(dat);
        }
        else if (x == "levelorder")
        {
            n.levelOrder();
            cout << endl;
        }
    }
    return 0;
}
