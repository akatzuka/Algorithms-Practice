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

void DFSHelper(GraphNode *origin, unordered_set<GraphNode *> &visited, string end, int &count)
{
  visited.insert(origin);
  for (GraphNode *neighbor : origin->neighbors)
  {
    if (neighbor->data == end)
    {
        return;
    }
    else if (visited.count(neighbor) == 0)
    {
        count++;
        DFSHelper(neighbor, visited, end, count);
    }
  }
}

void DFS(GraphNode *origin, string end, int &count) {
    auto visited = unordered_set<GraphNode *>();
    DFSHelper(origin, visited, end, count);
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
    string start, goal;
    int num_loc, count = 0;

    getline(cin, start);
    getline(cin, goal);
    cin >> num_loc;
    cin.ignore();

    int shape, check = 1;

    string in;
    vector<unordered_set<GraphNode *>> finalSet;
    vector<string> words;
    vector<string> wordsSplit;
    vector<GraphNode *> n;

    for (int i=0; i < num_loc; i++)
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
        if(n[i]->data == start)
        {
            DFS(n[i], goal, count);
            break;
        }
    }
    if (count == 0)
    {
        count++;
    }
    cout << count << endl;

    return 0;
}
