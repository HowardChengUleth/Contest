#include <bits/stdc++.h>

using namespace std;

bool valid(string line)
{
  for (auto &c : line) {
    if (c == '-' || c == ':') {
      c = ' ';
    }
  }

  istringstream iss(line);

  int lo, hi;
  char ch;
  iss >> lo >> hi >> ch;

  int count = 0;
  string s;
  while (iss >> s) {
    if (lo-1 < s.length())
      count += s[lo-1] == ch;
    if (hi-1 < s.length())
      count += s[hi-1] == ch;
  }

  return count == 1;
}

int main()
{
  string line;

  int count = 0;
  while (getline(cin, line)) {
    count += valid(line);
  }
  cout << count << endl;
    

  return 0;
}
