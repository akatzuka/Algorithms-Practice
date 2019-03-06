//Took inspiration from geeksforgeeks code, stackoverflow question suggestions, and some code from Emma's repl.it for Floyd

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include <climits>
using namespace std;

//struct for queries, also gets weights for each and has a function to print the weight at the end
struct Query
{
  string a, b;
  int w;

  Query() {}

  void set(string s)
  {
    vector<string> text;

    int i = 0;
    string hold;

    while (i <= s.length())
    {
        if (s[i] == ',' || i == s.length())
        {
            text.push_back(hold);
            hold = "";
            i++;
        }
        else
        {
            hold += s[i];
        }
        i++;
    }

    a = text[0];
    b = text[1];
    w = stoi(text[2]);
  }

  void print()
  {
    cout << a << " " << b << " " << w << endl;
  }
};


struct Matrix {
  vector<string> data;
  vector<vector<int>> temp;
  vector<vector<int>> edges;
  unordered_map<string, int> indices;

  Matrix(vector<string> data)
  {
    this->data = data;
    temp = vector<vector<int>>(data.size(), vector<int>(data.size(), INT_MAX));
  }

    int lookup(string source, string destination) //looks up specific edge
    {
        int x = indices[source];
        int y = indices[destination];
        return edges[x][y];
    }

    void createMatrix(vector<Query> &queries)   //generates a matrix from the queries vector
    {
        for (int i = 0; i < data.size(); i++) //initialize temp matrix to 0's
        {
            temp[i][i] = 0;
        }

        for (int i = 0; i < data.size(); i++) //initialze the indices map
        {
            indices[data[i]] = i;
        }

        for (Query query : queries)           //for all queries in the query vector, pull the x,y coords from the indices map and weight, and set matrix at coords to that weight
        {
            int x = indices[query.a];
            int y = indices[query.b];
            int weight = query.w;

            temp[x][y] = weight;
            temp[y][x] = weight;
        }
        edges = temp;     //set edges matrix equal to temp
    }

  void floyd()  //floyd pathfinding algorithm
  {
    for(int k = 0; k < edges.size(); k++)
    {
      for (int i = 0; i < edges.size(); i++)
      {
        for (int j = 0; j < edges.size(); j++)
        {
          if (edges[i][k] == INT_MAX || edges[k][j] == INT_MAX)
          {
            continue;
          }

          if (edges[i][j] > edges[i][k] + edges[k][j])
          {
            edges[i][j] = edges[i][k] + edges[k][j];
          }
        }
      }
    }
  }

  void print()  //print function for printing the matrix
  {
    for (int i = 0; i < temp.size(); i++)
    {
      for (int j = 0; j < temp.size(); j++)
      {
        cout << temp[i][j] << " ";
      }
      cout << endl;
    }
  }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    //initialize variables to store counts and read in number of people
    int people_num, service_num, queries_num;
    cin >> people_num;

    //initialize vectors
    vector<string> people(people_num);
    vector<string> data;

    for (auto &i : people)      //just figured out how to actually use the type auto, its really useful, push people input into data
    {
        cin >> i;
        data.push_back(i);
    }

    cin >> service_num;

    //initialize service vector and read in and push to data vector
    vector<string> services(service_num);

    for (auto &i : services)
    {
        cin >> i;
        data.push_back(i);
    }

    //sort vectors before pathfinding

    sort(people.begin(), people.end());
    sort(data.begin(), data.end());
    sort(services.begin(), services.end());

    cin >> queries_num;
    cin.ignore();

    vector<Query> queries;
    string str;

    while(queries_num--)
    {
        getline(cin, str);
        Query qur;
        qur.set(str);
        queries.push_back(qur);
    }

    //create matrix
    Matrix matrix(data);
    matrix.createMatrix(queries);

    matrix.floyd();

    //Output - printing
    for (auto j : services)
    {
        cout << j << " ";
    }
    cout << endl;

    for (auto p : people)
    {
        for (auto s : services)
        {
               cout << matrix.lookup(p, s) << " ";
        }
        cout << p << endl;
    }

    return 0;
}
