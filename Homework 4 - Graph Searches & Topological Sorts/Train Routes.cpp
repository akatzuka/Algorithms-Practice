#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <stack>
#include <queue>
#include <unordered_set>
using namespace std;

struct GraphNode {
  string data;
  vector<GraphNode *> neighbors;
 public:
  GraphNode(string n) {
    data = n;
    neighbors = vector<GraphNode *>();
  }
};

void DFSHelper(GraphNode *origin, unordered_set<GraphNode *> &visited)
{
  visited.insert(origin);
  for (GraphNode *neighbor : origin->neighbors)
  {
    if (visited.count(neighbor) == 0)
    {
        DFSHelper(neighbor, visited);
    }
  }
}

unordered_set<GraphNode *> DFS(GraphNode *origin) {
    auto visited = unordered_set<GraphNode *>();
    DFSHelper(origin, visited);
    return visited;
}

void trim(string &s)
{
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);
    p = s.find_last_not_of(" \t");
    if (string::npos != p)
    {
        s.erase(p + 1);
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int shape, check = 1;
    cin >> shape;
    cin.ignore();

    string in;
    vector<unordered_set<GraphNode *>> finalSet;
    vector<string> words;
    vector<string> wordsSplit;
    vector<GraphNode *> n;

    for (int i=0; i < shape; i++)
    {
        getline(cin, in);
        stringstream stringStream(in);
        string line;
        while(getline(stringStream, line, ':'))
        {
            trim(line);
            words.push_back(line);
        }
        n.push_back(new GraphNode(words[0]));
        wordsSplit.push_back(words[1]);
        trim(wordsSplit[i]);
        words.clear();
    }

    for(int i = 0; i < n.size(); i++)
    {
        stringstream stringStream(wordsSplit[i]);
        string l;
        while(getline(stringStream, l, ','))
        {
            trim(l);
            words.push_back(l);
        }
        for (int j = 0; j < words.size(); j++)
        {
            for(int q = 0; q < n.size(); q++)
            {
                if(words[j] == n[q]->data)
                {
                    n[i]->neighbors.push_back(n[q]);
                }
            }
        }
        words.clear();
    }
    for(int i = 0; i < n.size(); i++)
    {
        check = -1;
        for(int z = 0; z < finalSet.size(); z++)
        {
            if(finalSet[z].find(n[i]) != finalSet[z].end())
            {
                check = 1;
                break;
            }
        }
        if(check == -1)
        {
            finalSet.push_back(DFS(n[i]));
        }
    }
    cout << finalSet.size() << endl;

    return 0;
}
