#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int max(vector<int> nums, int n)
{
    int m = nums[0];
    for (int i = 1; i < n; i++)
        if (nums[i] > m)
            m = nums[i];
    return m;
}

void trim(string& s) {
  size_t p = s.find_first_not_of(" \t");
  s.erase(0, p);
  p = s.find_last_not_of(" \t");
  if (string::npos != p)
     s.erase(p+1);
}

void countingSort(vector<int> &vec, int number) {
  vector<int> copy = vec;
  auto counts = vector<int>(10, 0);
  // For radix, i should be a single digit, not the whole number
  // Count how many numbers there are for each number 0-9, for each digit
  for (int i = 0; i < vec.size(); i++)
  {
     counts[(copy[i]/number) % 10]++;
  }

  //Add the previous count to current count
  for(int i = 1; i < counts.size(); i++)
  {
      counts[i] += counts[i - 1];
  }
  for (int j = vec.size() - 1; j >= 0; j--)
  {
    vec[counts[(copy[j] / number) % 10] - 1] = copy[j];
    counts[(copy[j] / number) % 10]--;
  }

}

void radixsort(vector<int> &vec)
{
    int max_num = max(vec, vec.size());
    for (int i = 1; max_num/i > 0; i *= 10)
    {
        countingSort(vec, i);
        for (int j = 0; j < vec.size(); j++)
        {
            cout << vec[j] << ", ";
        }
        cout << endl;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    vector<int> nums;
    string input;
    getline(cin, input);

    stringstream ss(input);
    string s_in;

    while(getline(ss, s_in, ','))
    {
        trim(s_in);
        nums.push_back(stoi(s_in));
    }

    radixsort(nums);

    return 0;
}
