#include <iostream>
#include <string>
#include <cctype>
#include <set>

using namespace std;

int main(void)
{
  string s;
  char c;
  set<string> S;
  
  while (cin.get(c)) {
    c = tolower(c);
    if (islower(c)) {
      s += c;
    } else if (c == '-') {
      if (cin.peek() == '\n') {
	cin.ignore();
      } else {
	s += c;
      }
    } else if (s.length() > 0) {
      S.insert(s);
      s = "";
    }
  }
  if (s.length() > 0) {
    S.insert(s);
    s = "";
  }

  for (set<string>::iterator it = S.begin(); it != S.end(); ++it) {
    cout << *it << endl;
  }

  return 0;
}
