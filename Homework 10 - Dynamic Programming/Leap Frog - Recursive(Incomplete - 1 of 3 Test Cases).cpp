#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <climits>
using namespace std;

void trim(string& s) {
  size_t p = s.find_first_not_of(" \t");
  s.erase(0, p);
  p = s.find_last_not_of(" \t");
  if (string::npos != p)
     s.erase(p+1);
}

int frogRecursive(vector<int> lily_pads, int num_lily, int current_index)
{
    if(current_index == lily_pads.size() - 1)
    {
        return 0;
    }
    if(lily_pads.size() <= lily_pads[current_index])
    {
        return 1;
    }
    if(lily_pads[current_index] == 0)
    {
        return INT_MAX;
    }

    int jumps = INT_MAX;
    for(int i = 1 ; i < num_lily && i <= lily_pads[current_index]; i++)
    {
        int t = frogRecursive(lily_pads, num_lily, current_index + i);
        if(t != INT_MAX)
        {
            jumps = min(jumps, 1 + t);
        }
        else
        {
            jumps = -1;
        }
    }
    return jumps;
}


int frogRecursiveWrapper(vector<int> lily_pads, int num_lily)
{
    unordered_map<int, int> lilyValues = {};
    lilyValues[0] = 1;
    lilyValues[1] = 1;
    return frogRecursive(lily_pads, num_lily, 0);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    int num_pads;
    vector<int> lilypads;
    cin >> num_pads;
    cin.ignore();

    string input;
    getline(cin, input);
    stringstream ss(input);
    string s_in;

    while(getline(ss, s_in, ' '))
    {
        trim(s_in);
        lilypads.push_back(stoi(s_in));
    }

    cout << frogRecursiveWrapper(lilypads, num_pads);

    return 0;
}
