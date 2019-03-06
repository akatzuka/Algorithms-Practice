#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void heapify(vector<int> &sNum, vector<string> &sF, vector<string> &sL, int size, int i)
{
    int largest = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;

    if (left < size && sNum[left] > sNum[largest] || (left < size && sNum[left] == sNum[largest] && sF[left] > sF[largest]) || (left < size && sNum[left] == sNum[largest] && sF[left] == sF[largest] && sL[left] > sL[largest]))
    {
        largest = left;
    }

    if (right < size && sNum[right] > sNum[largest] || (right < size && sNum[right] == sNum[largest] && sF[right] > sF[largest]) || (right < size && sNum[right] == sNum[largest] && sF[right] == sF[largest] && sL[right] > sL[largest]))
    {
        largest = right;
    }

    if(largest != i)
    {
        swap(sNum[i], sNum[largest]);
        swap(sF[i], sF[largest]);
        swap(sL[i], sL[largest]);
        heapify(sNum, sF, sL, size, largest);
    }
}

void makeHeap(vector<int> &sNum, vector<string> &sF, vector<string> &sL, int size)
{
  for(int i = (size / 2) - 1; i >= 0; i--)
  {
      heapify(sNum, sF, sL, size, i);
  }

  for(int i = size - 1; i >= 0; i--)
  {
      for(int q = 0; q < size; q++)
      {
          cout << sF[q] << " " << sL[q] << " " << sNum[q] << endl;
      }
      cout << endl;

      swap(sNum[0], sNum[i]);
      swap(sF[0], sF[i]);
      swap(sL[0], sL[i]);

      heapify(sNum, sF, sL, i, 0);
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
    makeHeap(sNum, sF, sL, sNum.size());

    return 0;
}
