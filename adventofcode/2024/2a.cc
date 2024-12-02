#include <bits/stdc++.h>

using namespace std;

bool safe(const string &line)
{
  istringstream iss(line);
  vector<int> v;

  int x;
  while (iss >> x) {
    v.push_back(x);
  }

  bool inc = false, dec = false;
  for (int i = 1; i < v.size(); i++) {
    int diff = v[i] - v[i-1];
    if (!(1 <= abs(diff) && abs(diff) <= 3)) {
      return false;
    }
    inc |= v[i] > v[i-1];
    dec |= v[i] < v[i-1];
  }
  return (inc && !dec) || (!inc && dec);
}

int main()
{
  string line;
  int ans = 0;
  
  while (getline(cin, line)) {
    if (safe(line)) {
      ans++;
    }
  }
  cout << ans << endl;

  return 0;
}
