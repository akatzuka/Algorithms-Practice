#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
using namespace std;

void trim(string& s) {
  size_t p = s.find_first_not_of(" \t");
  s.erase(0, p);
  p = s.find_last_not_of(" \t");
  if (string::npos != p)
     s.erase(p+1);
}

int stepRecursive(vector<int> &steps, vector<int> &m_cost, int num_steps)
{
    if (num_steps < 0)
    {
        return 0;
    }
    if (m_cost[num_steps] > 0)
    {
        return m_cost[num_steps];
    }
    return m_cost[num_steps] = min(stepRecursive(steps, m_cost, num_steps - 1), stepRecursive(steps, m_cost, num_steps - 2)) + steps[num_steps];
}

int stepRecursiveWrapper(vector<int> steps, int num_steps) {
   vector<int> m_cost(steps.size() + 1);

   return min(stepRecursive(steps, m_cost, num_steps - 1), stepRecursive(steps, m_cost, num_steps - 2)) + steps[num_steps - 1];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    int num_steps;
    vector<int> stair_costs;
    cin >> num_steps;
    cin.ignore();

    string input;
    getline(cin, input);
    stringstream ss(input);
    string s_in;

    while(getline(ss, s_in, ' '))
    {
        trim(s_in);
        stair_costs.push_back(stoi(s_in));
    }

    cout << stepRecursiveWrapper(stair_costs, num_steps);

    return 0;
}
