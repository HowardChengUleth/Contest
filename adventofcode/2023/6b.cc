#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void read_vec(vector<ll> &v)
{
  string dummy, line;
  cin >> dummy;
  getline(cin, line);

  string line2;
  for (auto c : line) {
    if (isdigit(c)) {
      line2 += c;
    }
  }
  istringstream iss(line2);
  ll x;
  while (iss >> x) {
    v.push_back(x);
  }

  for (auto x : v) {
    cout << x << endl;
  }
  cout << "=======" << endl;
}

ll find_ways(ll t, ll d)
{
  ll count = 0;
  for (ll hold = 0; hold <= t; hold++) {
    ll speed = hold;
    ll dist = (t - hold) * speed;
    if (dist > d) {
      count++;
    }
  }
  return count;
}

int main()
{
  string dummy, line;

  vector<ll> time, dist;
  read_vec(time);
  read_vec(dist);

  int n = time.size();
  ll ans = 1;
  for (int i = 0; i < n; i++) {
    ans *= find_ways(time[i], dist[i]);
  }
  cout << ans << endl;

  return 0;
}
