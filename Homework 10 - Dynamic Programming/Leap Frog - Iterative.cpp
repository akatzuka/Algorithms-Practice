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

int frogIterative(vector<int> lilypads, int num_pads) {
    unordered_map<int, int> jumpValues = {};

    jumpValues[0] = 1;

    int j = 0;
    int current_index = 0;
    for(int i = num_pads - 2; i >= 0; i--)
    {
        if(lilypads[i] == 0)
        {
            jumpValues[i] = 999999;
        }
        else if(lilypads[i] >= (num_pads - i - 1))
        {
            jumpValues[i] = 1;
        }
        else
        {
            int min_num = 50;
            for(int j = i + 1; j < num_pads && j <= lilypads[i] + i; j++)
            {
                if (min_num > jumpValues[j])
                {
                    min_num = jumpValues[j];
                }
            }
            if (min_num != 50)
            {
                jumpValues[i] = min_num + 1;
            }
            else
            {
                jumpValues[i] = -1;
            }
        }
    }
    return jumpValues[0];
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

    cout << frogIterative(lilypads, num_pads);

    return 0;
}
