#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void linearSearch(vector <string> &v, vector <string> &t) {

    for (int i = 0; i < t.size(); i++)
    {
        int q = -1;
        for(int j =0; j < v.size(); j++)
        {
            if(t[i] == v[j])
            {
                cout << j << ": " << j + 1 << endl;
                q = 0;
            }
        }
        if (q == -1)
        {
            cout << q << ": " << v.size() << endl;
        }
    }
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
    linearSearch(books, target);
    return 0;
}
