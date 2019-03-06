#include <iostream>
#include <queue>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
  int height;
 public:
  Node(int d) {
    data = d;
    left = nullptr;
    right = nullptr;
    height = 1;
  }
};

class AVL {
    Node *root;

  private:
    Node *rotateLeft(Node *curr) {
      Node *temp = curr->right;
      curr->right = temp->left;
      temp->left = curr;
      curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
      temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));
      return temp;
    }

    Node *rotateRight(Node *curr) {
      Node *temp = curr->left;
      curr->left = temp->right;
      temp->right = curr;
      curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
      temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));
      return temp;
    }

    int getHeight(Node *curr) {
      if (!curr)
        return 0;
      return curr->height;
    }

    int getBalance(Node *curr) {
      int l = getHeight(curr->left);
      int r = getHeight(curr->right);
      return l-r;
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

    Node* ins(Node *root, int data) {
        if (!root)
          {
            root = new Node(data);
            return root;
          }
        if (root->data > data)
          {
            root->left = ins(root->left, data);
          }
        else
          {
            root->right = ins(root->right, data);
          }
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
        int rootBalance =  getBalance(root);
        if (abs(rootBalance) > 1)
          {
            if (rootBalance > 1)
            {
                if (getBalance(root->left) < 0)
                {
                    root->left = rotateLeft(root->left);
                }
                root = rotateRight(root);
            }
            if (rootBalance < -1)
            {
                if (getBalance(root->right) > 0)
                {
                    root->right = rotateRight(root->right);
                }
                root = rotateLeft(root);
            }
          }
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        return root;
    }

    void level(Node *root) {
      auto q = queue<Node *>();
      q.push(root);
      while(!q.empty()) {
        Node *temp = q.front();
        q.pop();
        cout << temp->data << "("<< getBalance(temp) << ") ";
        if (temp->left)
          q.push(temp->left);
        if (temp->right)
          q.push(temp->right);
        }
    }

    Node* rem(Node *root, int target) {
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
        int rootBalance =  getBalance(root);
        if (abs(rootBalance) > 1)
          {
            if (rootBalance > 1)
            {
                if (getBalance(root->left) < 0)
                {
                    root->left = rotateLeft(root->left);
                }
                root = rotateRight(root);
            }
            if (rootBalance < -1)
            {
                if (getBalance(root->right) > 0)
                {
                    root->right = rotateRight(root->right);
                }
                root = rotateLeft(root);
            }
          }
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        return root;
    }

  public:
    AVL() {
        root = NULL;
    }
    bool lookup(int target)
    {
        return look(root, target);
    }
    void insert(int data) {
        root = ins(root, data);
    }
    void levelOrder(){
        level(root);
    }
    void remove(int target){
        root = rem(root, target);
    }
};

int main() {

    //initialze variables
    AVL n;
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
