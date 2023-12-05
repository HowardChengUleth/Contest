#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> seeds;

string dummy;

void read_seeds()
{
  cin >> dummy;
  getline(cin, dummy);
  istringstream iss(dummy);

  ll x;
  while (iss >> x) {
    seeds.push_back(x);
  }
  getline(cin, dummy);
}

void read_map()
{
  getline(cin, dummy);
  vector<ll> dest, src, len;
  while (getline(cin, dummy) && dummy != "") {
    istringstream iss(dummy);
    ll a, b, c;
    iss >> a >> b >> c;
    dest.push_back(a);
    src.push_back(b);
    len.push_back(c);
  }

  int n = dest.size();
  for (auto &s : seeds) {
    for (int i = 0; i < n; i++) {
      if (src[i] <= s && s < src[i] + len[i]) {
	s += dest[i] - src[i];
	break;
      }
    }
  }
}

int main()
{
  read_seeds();

  for (int i = 0; i < 7; i++) {
    read_map();
  }
  cout << *min_element(begin(seeds), end(seeds)) << endl;
  return 0;
}
