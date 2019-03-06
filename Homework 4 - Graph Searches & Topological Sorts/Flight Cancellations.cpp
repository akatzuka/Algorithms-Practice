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

vector<GraphNode *> n;
string origin, destination;
bool found = false;

bool DFSHelper(GraphNode *origin, unordered_set<GraphNode *> &visited, GraphNode *target)
{
  visited.insert(origin);
  for (GraphNode *neighbor : origin->neighbors)
  {
    if (visited.count(neighbor) == 0)
    {
        if(neighbor==target)
        {
            found = true;
        }
        DFSHelper(neighbor, visited, target);
    }
  }
    if(found)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void DFS(GraphNode *origin, GraphNode *target) {
    auto visited = unordered_set<GraphNode *>();
    DFSHelper(origin, visited, target);
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
    string first, second;
    int num_cities = 0;

    getline(cin, origin);
    getline(cin, destination);
    cin >> num_cities;
    cin.ignore();

    string in;
    string delimiter(":,");
    vector<string> words;
    vector<string> wordsSplit;
    vector<string> final;

    for (int i=0; i < num_cities; i++)
    {
        getline(cin, in);
        stringstream stringStream(in);
        string line;
        while(getline(stringStream, line))
        {
            size_t previous = 0, pos;
            while((pos = line.find_first_of(":", previous)) != std::string::npos)
            {
                if(pos > previous)
                {
                    words.push_back(line.substr(previous,pos - previous));
                }
                previous = pos + 1;
            }
            if (previous < line.length())
            {
                words.push_back(line.substr(previous, std::string::npos));
            }
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

//DFS
    GraphNode* original;
    GraphNode* goal;

    for(auto q : n)
    {
        if(destination == q->data)
        {
            goal = q;
        }
        if(origin == q->data)
        {
            original = q;
        }
    }

    for (int i = 0; i < n.size(); i++)
    {
        if (n[i]->data == origin)
        {
            for (int j = 0; j < n[i]->neighbors.size(); j++)
            {
                if (n[i]->neighbors[j]->data == destination)
                {
                    n[i]->neighbors.erase(n[i]->neighbors.begin() + j);
                }
            }

        }
        if (n[i]->data == destination)
        {
            for (int j = 0; j < n[i]->neighbors.size(); j++)
            {
                if (n[i]->neighbors[j]->data == origin)
                {
                    n[i]->neighbors.erase(n[i]->neighbors.begin() + j);
                }
            }
        }
    }
    DFS(original, goal);

    if (found)
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "False" << endl;
    }

    return 0;
}
