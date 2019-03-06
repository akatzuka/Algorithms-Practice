#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class MaxHeap {
    vector<int> data;
  public:
    MaxHeap() {
        // ...
    }
    int size() {
        cout << data.size() << endl;
        return 0;
    }
    int maxLookup() {
        int max = 0;
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i] > max)
            {
                max = data[i];
            }
        }
        cout << max << endl;
        return 0;
    }
    void extractMax() {
        int max = 0, loc = 0;
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i] > max)
            {
                max = data[i];
                loc = i;
            }
        }
        data.erase(data.begin() + loc);
    }
    void insert(int data2) {
        data.push_back(data2);
    }
    void remove(int index) {
        data.erase(data.begin() + index);
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int commands;
    cin >> commands;
    string input;
    int dat;

    MaxHeap heapo;

    for (int i = 0; i < commands; i++)
    {
        cin >> input;
        if (input == "size")
        {
            heapo.size();
        }
        else if (input == "insert")
        {
            cin >> dat;
            heapo.insert(dat);
        }
        else if (input == "maxLookup")
        {
            heapo.maxLookup();
        }
        else if (input == "extractMax")
        {
            heapo.extractMax();
        }
        else if (input == "delete")
        {
            cin >> dat;
            heapo.remove(dat);
        }
    }
    return 0;
}
