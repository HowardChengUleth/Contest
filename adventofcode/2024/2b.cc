#include <bits/stdc++.h>

using namespace std;

bool safe1(const vector<int> &v)
{
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

bool safe(const string &line)
{
  istringstream iss(line);
  vector<int> v;

  int x;
  while (iss >> x) {
    v.push_back(x);
  }

  if (safe1(v)) {
    return true;
  }

  for (int i = 0; i < v.size(); i++) {
    vector<int> w;
    for (int j = 0; j < v.size(); j++) {
      if (i != j) {
	w.push_back(v[j]);
      }
    }
    if (safe1(w)) {
      return true;
    }
  }

  return false;
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
