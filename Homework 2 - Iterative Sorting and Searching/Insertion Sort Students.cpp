#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//Simple swap function for swapping ints
void swapI(vector<int> &in, int b)
{
    int tmp = in[b];
    in[b] = in[b - 1];
    in[b - 1] = tmp;
}

//Simple swap function for swapping strings
void swapS(vector<string> &s, int b)
{
    string tmp = s[b];
    s[b] = s[b - 1];
    s[b - 1] = tmp;
}

//Insertion sort function
void InSort(vector<int> &sNum, vector<string> &sF, vector<string> &sL)
{
    for (int i = 1; i < sNum.size(); i++)
    {
        for (int j = i; j > 0; j--)
        {
            //if statement compares years and swaps if previous year is greater then current
            if (sNum[j-1] > sNum[j])
            {
                swapI(sNum, j);
                swapS(sF, j);
                swapS(sL, j);
            }
        }
        for (int j = i; j > 0; j--)
        {
              //if statement compares years and first names and swaps if previous year is greater then current and if first name is alphabetically earlier
            if (sNum[j-1] == sNum[j] && sF[j-1].compare(sF[j])>0)
            {
                swapI(sNum, j);
                swapS(sF, j);
                swapS(sL, j);
            }
            //else if statement compares years and first/last names and swaps if previous year is greater then current and if first name and last name are alphabetically earlier
            else if (sNum[j-1] == sNum[j] && sF[j-1].compare(sF[j]) == 0 && sL[j-1].compare(sL[j])>0)
            {
                swapI(sNum, j);
                swapS(sF, j);
                swapS(sL, j);
            }
        }
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
    InSort(sNum, sF, sL);
    return 0;
}
