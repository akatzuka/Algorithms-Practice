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

int coinIterative(vector<int> coins, int sum, int num_coins) {
    unordered_map<int, int> coinValues = {};
    int vec_size = coins.size();

    coinValues[0] = 1;

    for(int i = 0; i < num_coins; i++)
    {
        for(int j = coins[i]; j <= sum; j++)
        {
            coinValues[j] += coinValues[j - coins[i]];
        }
    }
    return coinValues[sum];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    int sum, num_coins;
    vector<int> coin_denoms;
    cin >> sum >> num_coins;
    cin.ignore();

    string input;
    getline(cin, input);
    stringstream ss(input);
    string s_in;

    while(getline(ss, s_in, ' '))
    {
        trim(s_in);
        coin_denoms.push_back(stoi(s_in));
    }

    cout << coinIterative(coin_denoms, sum, num_coins);

    return 0;
}
