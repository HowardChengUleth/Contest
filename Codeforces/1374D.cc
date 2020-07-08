#include <bits/stdc++.h>

using namespace std;

// if a_i != 0 mod k, then it can only be adjusted when x = k - a_i
// mod k.  So we can count how many times each x = k - a_i mod k
// occurs, and that's the number of cycles x = 0,1,..., k-1 is needed
// (the last one may be incomplete) to modify those elements

void solve()
{
  map<int,int> M;

  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    a %= k;
    M[(k-a)%k]++;
  }

  pair<int,int> best{0,0};
  for (auto p : M) {
    int k = p.first, v = p.second;
    if (!k) continue;    // no need to modify

    best = max(best, make_pair(v,k));
  }

  cout << (long long)k*max(0,best.first-1) + (best.second ? best.second+1 : 0) << endl;

}


int main()
{
  int t;
  cin >> t;
  while (t--)
    solve();

  return 0;
}

