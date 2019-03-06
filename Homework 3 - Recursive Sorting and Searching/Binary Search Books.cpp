#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void binarySearch(vector <string> &v, string x) {
    int first = 0, last = v.size() - 1, middle;
    bool found = false;
    int count = 0;
    while(!found &&  first <= last)
    {
        middle = (first + last) / 2;
        if (v[middle] == x)
        {
            cout << middle << ": " << count + 1<< endl;
            return;
        }
        else if (v[middle] > x)
        {
            last = middle - 1;
            count++;
        }
        else
        {
            first = middle + 1;
            count++;
        }
    }
    cout << -1  << ": " << count << endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n,m;
    cin >> n;
    cin.ignore();
    vector<string> books (n);

    for (int i = 0; i < books.size(); i++)
    {
        getline(cin, books[i]);
    }

    cin >> m;
    cin.ignore();

    vector<string> target (m);
    for (int j = 0; j < target.size(); j++)
    {
        getline(cin,target[j]);

    }

    for (int q = 0; q < m; q++)
    {
        binarySearch(books, target[q]);
    }
    return 0;
}
