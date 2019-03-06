#include <cmath>
#include <cstdio>
#include <queue>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;
    public:
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};
class BST {
    Node *root;

    bool s(Node *root, int target)
    {
      if (root == NULL)
        return false;
      if (root->data == target)
        return true;
      if (root->data < target)
        return s(root->right, target);
      else
        return s(root->left, target);
    }
    Node* insertto(Node *root, int data) {
            if (root == NULL){
                root = new Node(data);
            }
            else if (root->data < data){
                root -> right = insertto(root->right, data);
            }
            else if (root->data > data){
                root -> left = insertto(root->left, data);
            }
            return root;
    }
    Node* Min(Node *root){
        if (root == NULL)
            return NULL;
        else if (root ->left)
            return Min(root->left);
        return root;
    }
    void preOrderP(Node *root) {
        if (root)
        {
            cout << root->data << " ";
            preOrderP(root->left);
            preOrderP(root->right);
        }
    }
    void postOrderP(Node *root) {
        if (root)
        {
            postOrderP(root->left);
            postOrderP(root->right);
            cout << root->data << " ";
        }
    }
    void inOrderP(Node *root) {
        if (root)
        {
            inOrderP(root->left);
            cout << root->data << " ";
            inOrderP(root->right);
        }
    }
    void levelOrderP(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        queue<Node *> q;
        q.push(root);

        while (1)
        {
            // nodeCount (queue size) indicates number of nodes
            // at current lelvel.
            int nodeCount = q.size();
            if (nodeCount == 0)
                break;

            // Dequeue all nodes of current level and Enqueue all
            // nodes of next level
            while (nodeCount > 0)
            {
                Node *node = q.front();
                cout << node->data << " ";
                q.pop();
                if (node->left != NULL)
                    q.push(node->left);
                if (node->right != NULL)
                    q.push(node->right);
                nodeCount--;
            }
        }
    }
    Node* deleteNodes(Node *root, int target) {
        Node* t;
        if(root == NULL)
            return NULL;
        else if (root -> data > target)
        {
            root->left = deleteNodes(root -> left, target);
        }
        else if (root -> data < target)
        {
            root -> right = deleteNodes(root -> right, target);
        }
        else if (root -> right && root -> left)
        {
            t = Min(root->right);
            root->data = t->data;
            root->right = deleteNodes(root->right, root->data);
        }
        else {
            t = root;
            if(root->left == NULL)
                root = root->right;
            else if (root-> right == NULL)
                root = root->left;
            delete t;
        }
        return root;
    }
  public:
    BST() {
        root = NULL;
    }
    bool lookup(int target) {
        return s(root, target);
    }
    void insert(int data) {
        root = insertto(root, data);
    }
    void preOrder(){
        preOrderP(root);
    }
    void postOrder(){
        postOrderP(root);
    }
    void inOrder(){
        inOrderP(root);
    }
    void levelOrder(){
        levelOrderP(root);
    }
    void remove(int target){
        root = deleteNodes(root, target);
    }
};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    BST n;
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
        else if (x == "preorder")
        {
            n.preOrder();
            cout << endl;
        }
        else if (x == "inorder")
        {
            n.inOrder();
            cout << endl;
        }
        else if (x == "postorder")
        {
            n.postOrder();
            cout << endl;
        }
        else if (x == "levelorder")
        {
            n.levelOrder();
            cout << endl;
        }
    }
    return 0;
}
