#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//Added comments for future reference

struct TrieNode{
  bool leaf;
  vector<TrieNode*> alpha; // 26

  TrieNode(){
    leaf = false;
    alpha = vector<TrieNode *>(26, nullptr);
  }

  bool hasChildren(){
    for(TrieNode *c: alpha)
      if(c)
        return true;
    return false;
  }
};

class Trie{
  TrieNode * root;

  public:
    Trie(){
      root = new TrieNode();
    }

    bool lookup(string str){
      TrieNode *curr = root;
      for(char c: str){     //iterate through trie, if current node is same then change curr, otherwise return false
        int ind = c - 'a';
        if(curr-> alpha[ind]){
          curr = curr -> alpha[ind];
        }
        else{
          return false;
        }
      }
      return curr -> leaf;  //return leaf number
    }

    void insert(string str){
      TrieNode *curr = root;
      for(char c: str){     //iterate through trie, if current node is same then change curr, otherwise create new trieNode
        int ind = c - 'a';
        if(curr-> alpha[ind]){
          curr = curr -> alpha[ind];
        }
        else{
          curr -> alpha[ind] = new TrieNode();
          curr = curr -> alpha[ind];
        }
      }
      curr -> leaf = true;
    }

    void alphabetical_helper(TrieNode* curr, string s){     //helper function for the alpha. function, prints out current node then loop through the next
      if(curr){
        if(curr -> leaf){
          cout << s << endl;
        }
        for(int i = 0; i < 26; i++){
          if(curr -> alpha[i]){
            alphabetical_helper(curr -> alpha[i], s + char(int('a')+ i));
          }
        }
      }
    }

    void alphabetical(string str){  //iterate through trie to find correct alpha order, then call alpha. helper function
      TrieNode *curr = root;
      for(char c: str){
        int ind = c - 'a';
        if(curr-> alpha[ind]){
          curr = curr -> alpha[ind];
        }
        else{
          return;
        }
      }
      alphabetical_helper(curr, str);

    }

    void removeHelper(string str, int pos, TrieNode *&curr){    //helper function for the remove function, if correct node is found, then deletes current node and sets node to null
      if(curr){
        if(pos == str.size()){
          curr -> leaf = false;
        }
        else{
          removeHelper(str, pos+1, curr-> alpha[str[pos]-'a']);
        }
      }


      if(!(curr -> leaf) && !curr->hasChildren()){
        delete curr;
        curr = nullptr;
        return;
      }
    }

    void remove(string str){    //remove function, just calls the helper that does the work
      removeHelper(str, 0, root);
    }

    void autocomplete_helper(TrieNode *curr, string prefix, int k){    //helper for autocomplete, prints out prefix string then recurs
      if(curr){
        if(curr -> leaf){
          cout << prefix << " ";
        }
        if(k == 0){
          return;
        }
        for(int i = 0; i < 26; i++){
          if(curr -> alpha[i]){
            autocomplete_helper(curr -> alpha[i], prefix + char(int('a')+ i), k-1);
          }
        }
      }
    }

    void autocomplete_negative(TrieNode* curr, string s){   //second helper for autocomplete, prints out prefix string then recurs, difference to the other function is this function is called if number provided to autocomplete is -1
      if(curr){
        if(curr -> leaf){
          cout << s << " ";
        }
        for(int i = 0; i < 26; i++){
          if(curr -> alpha[i]){
            autocomplete_negative(curr -> alpha[i], s + char(int('a')+ i));
          }
        }
      }
    }

    void autocomplete(string str, int k){    //autocomplete function that iterates through trie tho find correct node, then calls the appropriate helper
      TrieNode *curr = root;
      for(char c: str){
        int ind = c - 'a';
        if(curr-> alpha[ind]){
          curr = curr -> alpha[ind];
        }
        else{
          cout << endl;
          return;
        }
      }
      if(k == -1){
        autocomplete_negative(curr, str);
      }
      else{
        autocomplete_helper(curr, str, k);
      }
      cout << endl;
    }

    int count_helper(TrieNode *curr){   //helper function for the count function, iterates through trie and if node is found, increments count, then returns count
      if(!curr){
        return 0;
      }
      int count = 0;
      for(int i = 0; i < 26; i++){
        if(curr -> alpha[i]){
          count += count_helper(curr -> alpha[i]);
        }
      }

      return count + (curr -> leaf);
    }

    int count(){    //count function, just calls the helper that does the work
      return count_helper(root);
    }

};

int main() {
/* Enter your code here. Read input from STDIN. Print output to STDOUT */
  Trie tree = Trie();
  int steps;
  cin >> steps;
  for(int i = 0; i < steps; i++){
    string direction;
    cin >> direction;
    if(direction == "lookup"){
      string num;
      cin >> num;
      cout << tree.lookup(num) << endl;
    }

    else if(direction == "insert"){
      string num;
      cin >> num;
      tree.insert(num);
    }
    else if(direction == "alphabetical"){
      tree.alphabetical("");
    }
    else if(direction == "autocomplete"){
      string pre;
      cin >> pre;
      int num;
      cin >> num;
      tree.autocomplete(pre, num);
    }
    else if(direction == "count"){
      cout << tree.count() << endl;
    }
    else if(direction == "remove"){
      string num;
      cin >> num;
      tree.remove(num);
    }
  }
  return 0;
}
