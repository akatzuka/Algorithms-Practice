#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <unordered_set>
using namespace std;

void trim(string& s) {
  size_t p = s.find_first_not_of(" \t");
  s.erase(0, p);
  p = s.find_last_not_of(" \t");
  if (string::npos != p)
     s.erase(p+1);
}


void bucketSort(vector<float> &vec, int low, int high)
{
    int v_size = vec.size();                                                //Get input vector size
    vector<float>  bucket[v_size];                                          //Vector of buckets
    float bucketRange = (1.0 * (high - low) / v_size);                      //Variable for bucket Range

    for (int i = 0; i < v_size; i++)                                        //Putting elements into buckets
    {
        int bucket_input = (vec[i] - low) / bucketRange + 0.0001;           //Index in current bucket
        bucket[bucket_input].push_back(vec[i]);                             //Push element into vector
    }
    for (int i = 0; i < v_size; i++)
    {
        for (int j = 0; j < bucket[i].size(); j++)
        {
          cout << bucket[i][j] << ", ";
        }
        cout << endl;
    }

    vec.clear();                                                            //clears initial vector to prepare for fill
    for (int i = 0; i < v_size; i++)
    {
       sort(bucket[i].begin(), bucket[i].end());                            //sorts buckets
    }
    for (int i = 0; i < v_size; i++)                                        //Concatenate all buckets back into vec
    {
        for (int j = 0; j < bucket[i].size(); j++)
        {
          vec.push_back(bucket[i][j]);
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    int one, two;
    cin >> one;
    cin >> two;
    cin.ignore();

    vector<float> nums;

    string input;
    getline(cin, input);

    stringstream ss(input);
    string s_in;

    while(getline(ss, s_in, ','))
    {
        trim(s_in);
        nums.push_back(stof(s_in));
    }

    bucketSort(nums, one, two);

    for(int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << ", ";
    }
    cout << endl;

  return 0;
}
