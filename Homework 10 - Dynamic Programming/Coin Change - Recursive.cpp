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

int coinRecursive(vector<int> coins, int num_coins, int sum, int current_coin) {
    if (sum == 0)           //if sum is 0, then there is only 1 solution, no coins
    {
        return 1;
    }
    if (sum < 0)            //if sum is less than 0, then there no solutions
    {
        return 0;
    }
    int ways = 0;            //I wanted to use a map for this count, but couldnt get it to work properly, using a single counter works

    for (int i = current_coin; i < num_coins; i++)
    {
        ways += coinRecursive(coins, num_coins, sum - coins[i], i);
    }

    return ways;
}

int coinRecursiveWrapper(vector<int> coins, int num_coins, int sum) {
    //unordered_map<int, int> coinValues = {};

    //coinValues[0] = 0;

    return coinRecursive(coins, num_coins, sum, 0);
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

    cout << coinRecursiveWrapper(coin_denoms, num_coins, sum);

    return 0;
}
