#include <bits/stdc++.h>

using namespace std;

void process(const string &s)
{
  for (int i = 0; i + 4 <= s.length(); i++) {
    string t = s.substr(i, 4);
    assert(t.length() == 4);
    sort(begin(t), end(t));

    bool bad = false;
    for (int i = 0; i < 3; i++) {
      if (t[i] == t[i+1]) {
	bad = true;
      }
    }
    if (!bad) {
      cout << i+4 << endl;
      return;
    }
  }
  assert(false);
}

int main()
{
  string line;
  while (getline(cin, line)) {
    process(line);
  }

  return 0;
}
