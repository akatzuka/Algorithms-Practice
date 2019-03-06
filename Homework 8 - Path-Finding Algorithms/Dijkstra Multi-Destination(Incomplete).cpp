#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map> // array of self-balancing trees (typically red-black)
#include <map> // red-black tree, log(n) insert, delete, lookup
#include <set>
#include <climits>
#include <cmath>

using namespace std;

struct GraphNode {
  char data;
  vector<pair<GraphNode *, int>> neighbors;
  // unordered_map<GraphNode *, int> neighbors;
 public:
  GraphNode(char d) {
    data = d;
    neighbors = {};
  }
};

struct ParsedString {
  string src;
  vector<pair<string, int> > neighbors;
  ParsedString(string s) {
    int i = 0;
    while (s[i] != ':')
    {
      i++;
    }

    src = s.substr(0, i);

    i += 2;

    string temp;
    pair<string, int> curr;

    while (i <= s.length())
    {
        if (s[i] == ':')
        {
            curr.first = temp;
            temp = "";
            i++;
        }
        else if (s[i] == ',' || i == s.length())
        {
            curr.second = stoi(temp);
            neighbors.push_back(curr);
            curr = pair<string, int>();
            temp = "";
            i++;
        }
        else
        {
           temp += s[i];
        }
    i++;
    }
  }
};

GraphNode *minDist(unordered_map<GraphNode *, int> &distances, unordered_set<GraphNode *> & visited) {
  GraphNode *ans = nullptr;
  int m = INT_MAX;
  for (auto p : distances)
    if (!visited.count(p.first) && p.second <= m) {
      m = p.second;
      ans = p.first;
    }
  return ans;
}

int dijkstra(GraphNode *origin, GraphNode *dest, vector<GraphNode *> &nodes) {
  auto visited = unordered_set<GraphNode *>();
  auto distances = unordered_map<GraphNode *, int>();
  for (GraphNode *node : nodes)
    distances[node] = INT_MAX;
  distances[origin] = 0;
  GraphNode *curr = origin;
  while (curr != dest && distances[curr] != INT_MAX) {
    visited.insert(curr);
    for (auto neighbor : curr->neighbors)
      if (!visited.count(neighbor.first))
        if (distances[neighbor.first] > distances[curr] + neighbor.second)
          distances[neighbor.first] = distances[curr] + neighbor.second;
    curr = minDist(distances, visited);
  }
  return distances[dest];
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    /*parser from slack: ParsedString parsedString("Home: CSUMB: 9, Bookworks: 2");
    what the object will now hold: string src *as* "Home";
    vector<pair<string, int>> neighbors *as* { {"CSUMB", 9}, {"Bookworks", 2} };
    */

    return 0;
}
