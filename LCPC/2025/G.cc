#include <bits/stdc++.h>

using namespace std;

int h, n, m, L;
vector<int> p, s;

double reduce(double h, int num_potions)
{
  // could be more efficient with cummulative sums/products...

  // do the potions first
  for (int i = 0; i < num_potions; i++) 
    h *= (100.0 - p[i])/100.0;

  for (int i = 0; i < min(m, L - num_potions); i++) {
    h -= s[i];
  }

  return h;
}

int main()
{
  cin >> h >> n >> m >> L;
  p.resize(n);
  s.resize(m);
  
  for (auto &x : p) {
    cin >> x;
  }

  for (auto &x : s) {
    cin >> x;
  }

  sort(rbegin(p), rend(p));
  sort(rbegin(s), rend(s));
    
  double best = h;
  for (int i = 0; i <= L && i <= n; i++) {
    best = min(best, reduce(h, i));
  }

  cout << setprecision(10) << fixed << best << endl;
  
  return 0;
}
