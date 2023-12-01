#include <bits/stdc++.h>

using namespace std;

int calib(const string &s)
{
  int first = -1, last;
  for (auto c : s) {
    if (isdigit(c)) {
      if (first == -1) {
	first = c - '0';
      }
      last = c - '0';
    }
  }
  return first * 10 + last;
}

int main()
{
  string line;
  int total = 0;
  while (getline(cin, line)) {
    total += calib(line);
  }

  cout << total << endl;

  return 0;
}
