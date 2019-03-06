#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void merge(vector<int> &sNum, vector<string> &sF, vector<string> &sL, int left, int right, int middle)
{
  // merges two sorted subarrays
  // left = first index in the left subarray
  // mmiddle = last index in the left subarray
  // right = last index in the right subarray
  // middle + 1 = first index in the right subarray

    vector<int> leftNum, rightNum;
    vector<string> leftFirst, rightFirst;
    vector<string> leftLast, rightLast;

    for (int i = left; i <= middle; i++)
    {
        leftNum.push_back(sNum[i]);
        leftFirst.push_back(sF[i]);
        leftLast.push_back(sL[i]);
    }

    for (int j = middle + 1; j <= right; j++)
    {
        rightNum.push_back(sNum[j]);
        rightFirst.push_back(sF[j]);
        rightLast.push_back(sL[j]);
    }

    int left_i = 0;
    int right_i = 0;
    int i = left;

    while(left_i < leftNum.size() && right_i < rightNum.size())
    {
        if (leftNum[left_i] < rightNum[right_i] || (leftNum[left_i] == rightNum[right_i] && leftFirst[left_i] < rightFirst[right_i]) || (leftNum[left_i] == rightNum[right_i] && leftFirst[left_i] == rightFirst[right_i] && leftLast[left_i] < rightLast[right_i]))
        {
            sNum[i] = leftNum[left_i];
            sF[i] = leftFirst[left_i];
            sL[i] = leftLast[left_i];
            left_i++;
        }
        else
        {
            sNum[i] = rightNum[right_i];
            sF[i] = rightFirst[right_i];
            sL[i] = rightLast[right_i];
            right_i++;
        }
        i++;
    }

    while(left_i < leftNum.size())
    {
        sNum[i] = leftNum[left_i];
        sF[i] = leftFirst[left_i];
        sL[i] = leftLast[left_i];
        left_i++;
        i++;
    }

    while(right_i < rightNum.size())
    {
        sNum[i] = rightNum[right_i];
        sF[i] = rightFirst[right_i];
        sL[i] = rightLast[right_i];
        right_i++;
        i++;
    }
}

void mergeSort(vector<int> &sNum, vector<string> &sF, vector<string> &sL, int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) / 2;
        mergeSort(sNum, sF, sL, left, middle); //left merge
        mergeSort(sNum, sF, sL, middle + 1, right); //right merge
        merge(sNum, sF, sL, left, right, middle); //final merge

        for(int q = 0; q < sNum.size(); q++)
        {
            cout << sF[q] << " " << sL[q] << " " << sNum[q] << endl;
        }
        cout << endl;
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
    mergeSort(sNum, sF, sL, 0, sNum.size() - 1);
    return 0;
}
