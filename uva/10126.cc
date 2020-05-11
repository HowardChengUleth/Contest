/* @JUDGE_ID: 1102NT 10126 C "" */

#include <iostream>
#include <cctype>
#include <string>
#include <map>

using namespace std;

string getword(void)
{
  string s;
  char c;

  while (cin.get(c) && !isalpha(c))
    ;
  s += c;
  while (cin.get(c) && isalpha(c)) {
    s += c;
  }
  cin.unget();
  return s;
}

void tolower(string &s)
{
  for (int i = 0; i < s.length(); i++) {
    s[i] = tolower(s[i]);
  }
}

int main(void)
{
  int n;
  bool found, first = true;

  while (cin >> n) {
    if (!first) {
      cout << endl;
    }
    first = false;

    map<string,int> count;
    string s;
    while ((s = getword()) != "EndOfText") {
      tolower(s);
      count[s]++;
    }
    found = false;
    for (map<string,int>::iterator p = count.begin(); p != count.end(); ++p) {
      if (p->second == n) {
	cout << p->first << endl;
	found = true;
      }
    }
    if (!found) {
      cout << "There is no such word." << endl;
    }
  }

  return 0;
}
