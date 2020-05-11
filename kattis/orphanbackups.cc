#include <bits/stdc++.h>

using namespace std;

set<string> image, backup, roots;

string root(const string &s)
{
  int c = 0;
  for (int i = s.length()-1; i >= 0; i--) {
    if (s[i] == '_') {
      if (++c == 2) {
	return s.substr(0, i);
      }
    }
  }
  assert(false);
}

int main()
{
  string s;

  while (getline(cin, s) && s != "") {
    image.insert(s);
  }

  while (getline(cin, s)) {
    backup.insert(s);
    roots.insert(root(s));
  }

  bool printed = false;
  for (const auto &n : backup) {
    if (image.count(root(n)) == 0) {
      cout << "F " << n << endl;
      printed = true;
    }
  }
  for (const auto &n : image) {
    if (roots.count(n) == 0) {
      cout << "I " << n << endl;
      printed = true;
    }
  }
  if (!printed) {
    cout << "No mismatches." << endl;
  }
  
  
  return 0;
}
