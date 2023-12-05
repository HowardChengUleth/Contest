#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

vector<pii> seeds;

string dummy;

void read_seeds()
{
  cin >> dummy;
  getline(cin, dummy);
  istringstream iss(dummy);

  ll x, y;
  while (iss >> x >> y) {
    seeds.emplace_back(x, y);
  }
  getline(cin, dummy);
}

void add_next(ll start, ll len, ll dest, ll src, ll maplen,
	      vector<pii> &next)
{
  // hack to say it is already mapped
  if (start < 0) {
    next.emplace_back(start, len);
    return;
  }
  
  ll last = start + len - 1;
  if (start < src) {
    if (last < src) {
      next.emplace_back(start, len);
    } else {
      ll len1 = src - start;
      next.emplace_back(start, len1);
      add_next(src, len - len1, dest, src, maplen, next);
    }
    return;
  }

  ll srclast = src + maplen - 1;
  if (last > srclast) {
    if (start > srclast) {
      next.emplace_back(start, len);
    } else {
      ll len1 = last - srclast;
      next.emplace_back(srclast+1, len1);
      add_next(start, len - len1, dest, src, maplen, next);
    }
    return;
  }

  assert(src <= start && last <= srclast);
  next.emplace_back(-(start - src + dest), len); // hack: neg successful replace
}

vector<pii> read_map()
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

  vector<pii> next = seeds;
  int n = dest.size();
  for (int i = 0; i < n; i++) {
    vector<pii> curr = next;
    next.clear();
    for (auto [s, l]: curr) {
      add_next(s, l, dest[i], src[i], len[i], next);
    }
  }

  for (auto &[s, l]: next) {
    s = abs(s);
  }
  return next;
}

void print_seeds()
{
  cout << "==========" << endl;
  for (auto [s, l] : seeds) {
    cout << "(" << s << ", " << l << ") ";
  }
  cout << endl;

}

int main()
{
  read_seeds();
  //  print_seeds();
  for (int i = 0; i < 7; i++) {
    seeds = read_map();
    //print_seeds();
  }
  cout << min_element(begin(seeds), end(seeds))->first << endl;
  return 0;
}
