#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct minHeap {

    char data;
    int freq;
    minHeap *left, *right;
    minHeap(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};


void Huffman(vector<char> data, vector<int> frequencies)
{
    int size = data.size();
    struct minHeap *left, *right, *top;

    for (int i = 0; i < size; ++i)
    {
        minHeap.push(new minHeap(data[i], frequencies[i]));
    }
    while(minHeap.size() != 1)
    {
        left = minHeap.top();   //minimum frequency to left
        minHeap.pop();
        right = minHeap.top();  //next minimum frequency to right
        minHeap.pop();
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string input;
    string output;

    getline(cin, input);
    getline(cin, output);

    vector<char> letters(input.begin(), input.end());

    /*for (int i = 0; i < letters.size(); i++)
    {
        cout << letters[i] << endl;
    }*/

    //cout << output << endl;

    //HuffmanCodes(arr, freq, size);

    return 0;
}
