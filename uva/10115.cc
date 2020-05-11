/* @JUDGE_ID: 1102NT 10115 C++ "" */

#include <iostream>
#include <string>

using namespace std;

int apply(string &s, string f, string t)
{
  int pos = s.find(f, 0);

  if (pos == string::npos) {
    return 0;
  } else {
    s.replace(pos, f.length(), t);
    return 1;
  }
}

int main(void)
{
  int rules;
  string from[10], to[10];
  string s;

  while (cin >> rules && rules > 0) {
    getline(cin, s);
    for (int i = 0; i < rules; i++) {
      getline(cin, from[i]);
      getline(cin, to[i]);
    }
    getline(cin, s);
    for (int i = 0; i < rules; i++)
      while (apply(s, from[i], to[i]))
	;
    cout << s << endl;
  }

  return 0;
}
