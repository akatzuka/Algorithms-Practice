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
  int data;
  vector<pair<GraphNode *, int>> neighbors;
  // unordered_map<GraphNode *, int> neighbors;
 public:
  GraphNode(int d) {
    data = d;
    neighbors = {};
  }
};

int heuristic(GraphNode *curr, GraphNode *goal) {
  // CODE
  return 1;
}

GraphNode *minDistAStar(unordered_map<GraphNode *, pair<int, int>> &distances, unordered_set<GraphNode *> & visited) {
  GraphNode *ans = nullptr;
  int m = INT_MAX;
  for (auto p : distances)
    if (!visited.count(p.first) && p.second.second + p.second.first <= m) {
      m = p.second.second + p.second.first;
      ans = p.first;
    }
  return ans;
}

int astar(GraphNode *origin, GraphNode *dest, vector<GraphNode *> &nodes) {
  auto visited = unordered_set<GraphNode *>();
  auto distances = unordered_map<GraphNode *, pair<int, int>>();
  distances[origin] = pair<int, int>(0, heuristic(origin, dest));
  GraphNode *curr = origin;
  while (curr != dest && curr) {
    visited.insert(curr);
    for (auto neighbor : curr->neighbors)
      if (!visited.count(neighbor.first))
        //distances[neighbor.first].first shortest distance we've seen to neighbor (can change) g
        //distances[neighbor.first].second estimated distance from neighbor to goal (never changes) h
        //distances[curr].first shortest distance we've seen to curr
        //distances[curr].second estimated distance from curr to goal
        //neighbor.second distance from curr
        if (!distances.count(neighbor.first))
          distances[neighbor.first] = pair<int, int>(distances[curr].first + neighbor.second, heuristic(neighbor.first, dest));
        else if (distances[neighbor.first].first > distances[curr].first + neighbor.second)
          distances[neighbor.first].first = distances[curr].first + neighbor.second;
    curr = minDistAStar(distances, visited);
  }
  return (curr ? distances[dest].first : INT_MAX);
}

void link_hor(GraphNode *origin, vector<GraphNode *> &nodes, int index, int dimension)
{
    if(index = 0)
    {
        origin->neighbors.push_back(nodes[index++]);
        return;
    }
    if(index == dimension)
    {
        origin->neighbors.push_back(nodes[index--]);
        return;
    }
    else
    {
        origin->neighbors.push_back(nodes[index--]);
        origin->neighbors.push_back(nodes[index++]);
        return;
    }
}
void link_ver(GraphNode *origin, vector<GraphNode *> &nodes, vector<GraphNode *> &nodes_above, vector<GraphNode *> &nodes_below, int index, int dimension)
{
    if(index = 0)
    {
        origin->neighbors.push_back(nodes_below[index++]);
        return;
    }
    if(index == dimension)
    {
        origin->neighbors.push_back(nodes_above[index--]);
        return;
    }
    else
    {
        origin->neighbors.push_back(nodes_above[index--]);
        origin->neighbors.push_back(nodes_below[index++]);
        return;
    }
}
void link_diag(GraphNode *origin, vector<GraphNode *> &nodes, vector<GraphNode *> &nodes_above, vector<GraphNode *> &nodes_below, int index_x, int index_y, int dimension)
{
    if(index_x = 0 && index_y == 0)
    {
        origin->neighbors.push_back(nodes_below[index_x++]);
        return;
    }
    else if(index_x == 0)
    {
        origin->neighbors.push_back(nodes_below[index_x--]);
        origin->neighbors.push_back(nodes_below[index_x++]);
        return;
    }
    else if(index_x == dimension && index_y == 0)
    {
        origin->neighbors.push_back(nodes_below[index_x--]);
        return;
    }
    else if(index_x == 0 && index_y == dimension)
    {
        origin->neighbors.push_back(nodes_above[index_x++]);
        return;
    }
    else if(index_y == dimension)
    {
        origin->neighbors.push_back(nodes_above[index_x--]);
        origin->neighbors.push_back(nodes_above[index_x++]);
        return;
    }
    else if(index_x == dimension && index_y == dimension)
    {
        origin->neighbors.push_back(nodes_above[index_x--]);
        return;
    }
    else if(index_x == 0 && index_y != dimension)
    {
        origin->neighbors.push_back(nodes_above[index_x++]);
        origin->neighbors.push_back(nodes_below[index_x++]);
    }
    else if(index_x == dimension && index_y != dimension)
    {
        origin->neighbors.push_back(nodes_above[index_x--]);
        origin->neighbors.push_back(nodes_below[index_x--]);
    }
    else
    {
        origin->neighbors.push_back(nodes_above[index_x--]);
        origin->neighbors.push_back(nodes_above[index_x++]);
        origin->neighbors.push_back(nodes_below[index_x--]);
        origin->neighbors.push_back(nodes_below[index_x++]);
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int dimension, start_row, start_column, end_row, end_column, direction;
    vector<vector<GraphNode *>> graph_new;
    vector<GraphNode *> graph_final;

    //read in graph dimension
    cin >> dimension;
    cin.ignore();

    //read in start row and column coordinates
    cin >> start_row;
    cin.ignore();
    cin >> start_column;
    cin.ignore();

    //read in end row and column coordinates
    cin >> end_row;
    cin.ignore();
    cin >> end_column;
    cin.ignore();

    //read in direction number value, either 4 (up, down, left, and right) or 8 (4, also includes diagonals)
    cin >> direction;
    cin.ignore();

    for (int i = 0; i < dimension; i++)
    {
        vector<GraphNode *> g();
        graph_new.push_back(g);
    }
    int node, j = 0, q = 1;
    for (int i = 0; i < dimension * dimension; i++)
    {
        cin >> node;
        GraphNode *n = new GraphNode(node);
        graph_new[j].push_back(n);
        q++;
        if(q == dimension)
        {
            j++;
            q = 1;
        }
        else
        {
            j++;
        }
    }
    j = 0, q = 0;
    for (int i = 0; i < dimension * dimension; i++)
    {
        link_hor(graph_new[j][q], graph_new[j], q, dimension);
        if(j == 0)
        {
            link_ver(graph_new[j][q], graph_new[j], NULL, graph_new[j++], q - 1, dimension);
            link_diag(graph_new[j][q], graph_new[j], NULL, graph_new[j++], j, q - 1, dimension);
        }
        else if(j == dimension)
        {
            link_ver(graph_new[j][q], graph_new[j], graph_new[j--], NULL, q - 1, dimension);
            link_diag(graph_new[j][q], graph_new[j], graph_new[j--], NULL, j, q - 1, dimension);
        }
        else
        {
            link_ver(graph_new[j][q], graph_new[j], graph_new[j--], graph_new[j++], q - 1, dimension);
            link_diag(graph_new[j][q], graph_new[j], graph_new[j--], graph_new[j++], j, q - 1, dimension);
        }

        if(q == dimension)
        {
            j++;
            q = 1;
        }
        else
        {
            j++;
        }
    }
    j = 0, q = 0;
    for (int i = 0; i < dimension * dimension; i++)
    {
        graph_final.push_back(graph_new[j][q]);
        if(q == dimension)
        {
            j++;
            q = 1;
        }
        else
        {
            j++;
        }
    }

    cout << astar(graph_new[start_row][start_column], graph_new[end_row][end_column], graph_final) << endl;
    return 0;
}
