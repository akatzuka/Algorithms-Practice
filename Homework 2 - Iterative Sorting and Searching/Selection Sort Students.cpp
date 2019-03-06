#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//Simple swap function for swapping ints
void swapI(vector<int> &in, int b, int min)
{
    int tmp = in[b];
    in[b] = in[min];
    in[min] = tmp;
}

//Simple swap function for swapping strings
void swapS(vector<string> &s, int b, int min)
{
    string tmp = s[b];
    s[b] = s[min];
    s[min] = tmp;
}

//Insertion sort function
void SelectSort(vector<int> &sNum, vector<string> &sF, vector<string> &sL)
{
    int min;
    for (int i = 0; i < sNum.size() - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < sNum.size(); j++)
        {
            //if statement compares years and swaps if previous year is greater then current
            if (sNum[min] > sNum[j])
            {
                min = j;
            }
        }
        for (int j = i + 1; j < sNum.size(); j++)
        {
            if (sNum[min] == sNum[j] && sF[min].compare(sF[j])>0)
            {
                min = j;
            }
            else if (sNum[min] == sNum[j] && sF[min].compare(sF[j]) == 0 && sL[min].compare(sL[j])>0)
            {
                min = j;
            }
        }
        swapI(sNum, i, min);
        swapS(sF, i, min);
        swapS(sL, i, min);
        for (int q = 0; q < sNum.size();q++)
        {
            cout << sF[q] << " " << sL[q] << " " << sNum[q] << endl;
        }
        if (i != sNum.size() - 1)
        {
            cout << endl;
        }
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
    SelectSort(sNum, sF, sL);
    return 0;
}
