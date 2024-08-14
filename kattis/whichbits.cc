#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

ull ask(ull a, ull b)
{
  cout << "q " << a << ' ' << b << endl;
  cout << flush;

  ull ans;
  cin >> ans;
  return ans;
}
  
set<ull> S;

void solve(ull lo, ull hi, ull count)
{
  if (count == 0 || hi < lo) return;
  if (hi - lo + 1 == count) {
    for (ull i = lo; i <= hi; i++) {
      S.insert(i);
    }
    return;
  }

  ull mid = lo + (hi-lo)/2;
  ull left = ask(lo, mid);
  solve(lo, mid, left);
  solve(mid+1, hi, count-left);
}

int main()
{
  ull lo = 0, hi = (1ULL << 63) - 1;

  ull ans = ask(lo, hi);
  
  solve(lo, hi, ans);

  cout << "a " << S.size();
  for (auto x : S) {
    cout << ' ' << x;
  }
  cout << endl;
  return 0;
}
