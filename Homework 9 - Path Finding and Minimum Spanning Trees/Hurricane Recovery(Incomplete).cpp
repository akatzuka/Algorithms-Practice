#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
 string data;
 vector<pair<Node *, int>> neighbors;
 public:
 Node(string d) {
   data = d;
 }
};

// Gets the "root" of the set a node in my MST is in
Node *rootNode(Node *curr, unordered_map<Node *, Node *> &sets) {
 Node *parent = curr;
 while(sets[parent])
   parent = sets[parent];
 return parent;
}

Node *minNode(unordered_map<Node *, pair<Node *, int>> &dist) {
 int mDist = INT_MAX;
 Node *mNode = nullptr;
 for (auto p : dist)
   if (p.second.second <= mDist) {
     mDist = p.second.second;
     mNode = p.first;
   }
 return mNode;
}

vector<pair<pair<Node *, Node*>, int>> prims(vector<Node *> &nodes) {
 auto ans = vector<pair<pair<Node *, Node*>, int>>();
 // initializes vector of pairs - this is the mst we will be returning
 auto dist = unordered_map<Node *, pair<Node *, int>>();
 // initializes map to keep track of distance of nodes from the mst
 for (Node *node : nodes)
 // add all the nodes to the map
   dist[node] = pair<Node *, int>(nullptr, INT_MAX);
   // start out with no edge connecting them to the mst because the mst is empty
 for (int i = 0; i < nodes.size(); i++) {
 // iterate over number of nodes because that is how many nodes will be in the mst
   Node *mNode = minNode(dist);
   // gets min node - the node with the smallest weight between it and ANY node in the mst
   if (dist[mNode].first != nullptr) {
   // checks this isn't the first node we picked
     auto p = pair<Node *, Node*>(mNode, dist[mNode].first);
     // creates the edge (pair of nodes) that connects the min node to the mst
     ans.push_back(pair<pair<Node *, Node*>, int>(p, dist[mNode].second));
     // adds the edge and its weight to the mst
   }
   dist.erase(mNode);
   // removes min node from map because we already chose it (already in the mst)
   for (auto neighbor : mNode->neighbors) {
   // iterate over the min node's neighbors to update shortest edges connecting remaining nodes to mst
     if (dist.count(neighbor.first) && neighbor.second < dist[neighbor.first].second)
     // compares weight of the edge to the min node to the weight of the edge we stored (connects the neighbor to some other node in the mst)
       dist[neighbor.first] = pair<Node *, int>(mNode, neighbor.second);
       // update value for neighbor to be the edge connecting it to the mst
   }
 }
 return ans;
 // return the mst
}

int main() {
   /* Enter your code here. Read input from STDIN. Print output to STDOUT */

   //string origin;
   //getline(cin, origin);
   int n;
   cin >> n;
   cin.ignore();
   unordered_map<string, Node *> m = {};
   vector<Node *> graph;

   for (int i = 0; i < n; i++)
   {
       string dest;
       getline(cin, dest);
       m[dest] = new Node(dest);
       graph.push_back(m[dest]);
   }

   int x;
   cin >> x;
   cin.ignore();

   for (int i = 0; i < x; i++)
   {
       string line;
       getline(cin, line);
       int j = line.find(',');
       string a = line.substr(0, j);
       int k = line.find(',', j+2);
       string b = line.substr(j+2, k - (j+2));
       string wStr;
       wStr = line.substr(k+2, int(line.size() - (k+2)));
       int w = stoi(wStr);
       m[a]->neighbors.push_back(pair<Node *, int>(m[b], w));
       m[b]->neighbors.push_back(pair<Node *, int>(m[a], w));
   }

   auto edges = prims(graph);
   int ans = 0;
   for (auto e : edges)
   ans += e.second;
   cout << ans << endl;

   return 0;
}
