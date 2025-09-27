#include <bits/stdc++.h>
#include <cassert>

using namespace std;

bool works(const vector<int> &SIN, int m)
{
  vector<bool> seen(m, false);

  for (auto x : SIN) {
    if (seen[x % m]) {
      return false;
    }
    seen[x % m] = true;
  }

  return true;
}

int main()
{
  int G;
  cin >> G;

  vector<int> SIN(G);
  for (auto &x : SIN) {
    cin >> x;
  }

  for (int m = 1; ; m++) {
    if (works(SIN, m)) {
      cout << m << endl;
      return 0;
    }
  }

  assert(false);

  return 0;
}
