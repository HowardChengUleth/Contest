#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

int main()
{
  ll A, B, T, ta, tb;
  cin >> A >> B >> T >> ta >> tb;

  ll C;
  cin >> C;
  
  vector<pii> need(C);
  for (auto &p : need) {
    cin >> p.first >> p.second;
    p.first = max(p.first, A);      // this doesn't affect the answer but
    p.second = max(p.second, B);    // makes processing easier
  }
  sort(begin(need), end(need));

  int ans = 0;
  priority_queue<int> b_val;
  
  // all skill levels that can achieved are of the form
  //
  // (A, B + T/tb) + t * (1/ta, -1/tb)    for t = 0..T
  for (auto [a, b] : need) {
    // A + t/ta >= a
    // t/ta >= a - A
    // t >= (a - A) * ta

    ll t = (a - A) * ta;
    if (t > T) continue;           // can never do it

    ll currB = B + (T-t) / tb;     // it's okay to floor because we are comparing against integers
    if (b <= currB) {
      b_val.push(b);
    }

    while (!b_val.empty() && b_val.top() > currB) {
      b_val.pop();
    }
      
    ans = max(ans, (int)b_val.size());
  }

  cout << ans << endl;

  return 0;
}
