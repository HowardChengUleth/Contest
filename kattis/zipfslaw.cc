#include <bits/stdc++.h>

using namespace std;

bool solve_case(bool first)
{
  int n;
  if (!(cin >> n)) {
    return false;
  }
  
  if (!first) {
    cout << endl;
  }

  // do all the work here
  map<string, int> freq;
  
  string line;
  while (getline(cin, line) && line != "EndOfText") {
    // break line into words
    for (auto &ch : line) {
      if (!isalpha(ch)) {
	ch = ' ';
      }
      ch = tolower(ch);
    }
    istringstream iss(line);
    string word;
    while (iss >> word) {
      freq[word]++;
    }
  }

  bool found = false;
  for (auto [key, val] : freq) {
    if (val == n) {
      found = true;
      cout << key << endl;
    }
  }

  if (!found) {
    cout << "There is no such word." << endl;
  }
  
  return true;
}

int main()
{
  bool first = true;
  while (solve_case(first)) {
    first = false;
  }

  
  return 0;
}
