#include <bits/stdc++.h>

using namespace std;

vector<pair<string, string>> dictionary;

void read_dictionary()
{
  string line;

  while (getline(cin, line) && line != "") {
    istringstream iss(line);

    string s1, s2;
    iss >> s1 >> s2;

    dictionary.push_back(make_pair(s2, s1));
  }

  sort(begin(dictionary), end(dictionary));
}

void translate()
{
  string word;
  while (cin >> word) {
    auto it = lower_bound(begin(dictionary), end(dictionary),
			  make_pair(word, string("")));
    if (it != end(dictionary) && it->first == word) {
      cout << it->second << endl;
    } else {
      cout << "eh" << endl;
    }
  }
}

int main()
{
  read_dictionary();

  translate();

  return 0;
}
