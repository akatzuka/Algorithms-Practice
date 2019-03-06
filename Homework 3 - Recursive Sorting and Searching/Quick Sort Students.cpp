#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
void swap(vector<T>&s, int a, int z)
{
    T temp = s[a];
    s[a] = s[z];
    s[z] = temp;
}

int partition(vector<int> &sNum, vector<string> &sF, vector<string> &sL, int l, int h) {
  // uses element in position (l + r) / 2 as pivot
  // moves elements smaller than pivot to its left
  // moves elements greater than pivot to its right
  // returns final position of pivot
    int pivot = (l + h) / 2;
    int i = l;
    int j = h - 1;

    swap(sNum, pivot, h);
    swap(sF, pivot, h);
    swap(sL, pivot, h);

    while(i<=j)
    {
        while(sNum[i] < sNum[h] || (sNum[i] == sNum[h] && sF[i] < sF[h])
            || (sNum[i] == sNum[h] && sF[i] == sL[h] && sL[i] < sL[h]))
        {
            i++;
        }
        while (sNum[j] > sNum[h] || (sNum[j] == sNum[h] && sF[j] > sF[h])
            || (sNum[j] == sNum[h] && sF[j] == sL[h] && sL[j] > sL[h]))
        {
            j--;
        }
        if(i < j)
        {
            swap(sNum, i, j);
            swap(sF, i, j);
            swap(sL, i, j);
            j--;
            i++;
        }
    }

    swap(sNum, h, i);
    swap(sF, h, i);
    swap(sL, h, i);
    return i;
}

void quickSort(vector<int> &sNum, vector<string> &sF, vector<string> &sL, int l, int h)
{
    if(l < h)
    {
        int part = partition(sNum, sF, sL, l, h);
        for(int i = 0; i < sNum.size(); i++)
        {
            cout << sF[i] << " " << sL[i] << " " << sNum[i] << endl;
        }
        cout << endl;
        quickSort(sNum, sF, sL, l, part - 1);
        quickSort(sNum, sF, sL, part + 1, h);
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    //Initialize Variables
    int num;
    cin >> num;
    //cout << num;
    vector<string> sF (num);
    vector<string> sL (num);
    vector<int> sNum (num);


    //Read in First Name, Last Name, and Year into the appropriate vectors
    for (int i = 0; i< sNum.size(); i++)
    {
        cin >> sF[i] >> sL[i] >> sNum[i];
    }
    //Run sort
    quickSort(sNum, sF, sL, 0, sNum.size() - 1);
    return 0;
}
