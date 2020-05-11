/* @JUDGE_ID: 1102NT 261 C++ "" */

#include <string>
#include <iostream>
#include <set>

using namespace std;

const int MAX_LEN = 100;

int first_nonwindow(const string &line)
{
  int n = line.length();
  set<string> substr[MAX_LEN+1];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      substr[i-j+1].insert(line.substr(j, i-j+1));
      if (substr[i-j+1].size() > i-j+1+1) {
	return i+1;
      }
    }
  }
  return 0;
}

int main(void)
{
  string line;
  int pos;

  while (getline(cin, line)) {
    if (pos = first_nonwindow(line)) {
      cout << "NO:" << pos << endl;
    } else {
      cout << "YES" << endl;
    }
  }

  return 0;
}
