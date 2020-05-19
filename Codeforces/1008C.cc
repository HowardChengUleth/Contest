#include <bits/stdc++.h>

using namespace std;

// look at the largest numbers and work down.  Keep replacing them smaller
// ones with largest ones.  We don't actually need to replace them.  Just keep
// track of how many we have done and how many are left

int main()
{
  int n;
  map<int, int> M;

  cin >> n;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    M[-a]++;        // sort in reverse
  }

  int moved = 0;
  int rem = 0;
  for (auto p : M) {
    int t = min(rem, p.second);
    rem -= t;
    moved += t;
    rem += p.second;
  }

  cout << moved << endl;
  return 0;
}
