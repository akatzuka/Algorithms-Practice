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

int stairCost(vector<int> stairs, int num_stairs)
{
    //Initialize map for storing stair cost values
    unordered_map<int, int> stairValues = {};
    stairValues[1] = 0;
    stairValues[2] = 0;

    //Iterate through the stair vector, storing the current stair cost sum
    for (int i = 0; i < num_stairs - 1; i++)
    {
        stairValues[0] = stairs[i] + min(stairValues[1], stairValues[2]);
        stairValues[2] = stairValues[1];
        stairValues[1] = stairValues[0];
    }

    return min(stairValues[1], stairValues[2]) + stairs[num_stairs - 1];
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

    cout << stairCost(stair_costs, num_steps);

    return 0;
}
