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

void BFS(GraphNode *origin, vector<string> &final, int end)
{
  queue<GraphNode *> q;
  unordered_set<GraphNode *> s;
  q.push(origin);
  q.push(nullptr);
  s.insert(origin);
  int level = 0;
  while(!q.empty()){
    auto curr = q.front();
    if (curr == nullptr)
    {
        q.push(nullptr);
        level++;
        q.pop();
        curr = q.front();
        if (level == end + 1)
        {
            break;
        }
    }
    for(auto n : curr->neighbors){
      if(!s.count(n)){
        q.push(n);
        s.insert(n);
      }
    }
    final.push_back(curr->data);
    q.pop();
  }
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
    int end,m;
    cin >> end;

    string start;
    cin >> start;

    cin >> m;
    cin.ignore();

    string in;
    string delimiter(":,");
    vector<string> words;
    vector<string> wordsSplit;
    vector<string> final;
    vector<GraphNode *> n;

    for (int i=0; i < m; i++)
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

    for(int i = 0; i < n.size(); i++)
    {
        if(n[i]->data == start)
        {
            BFS(n[i], final, end);
            break;
        }
    }

    sort(final.begin(), final.end());

    for(int i = 0; i < final.size(); i++)
    {
        cout << final[i] << endl;
    }

    return 0;
}
