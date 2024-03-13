#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
int l;
int n;

struct Ship
{
  ll t, x, y, w;

  // adjust the time to "last", and add l to the length of the ship
  // to pretend Tom's ship is a point
  void adjust(ll last, ll l)
  {
    // move the ship over
    x -= last - t;
    
    // add l to the length of the ship (on the left end)
    x -= l;
    w += l;
  }

  // return [start,end] of where Tom cannot start
  pii forbidden() const
  {
    return make_pair(x-y, x+w-y);
  }
};

istream &operator>>(istream &is, Ship &s)
{
  return is >> s.t >> s.x >> s.y >> s.w;
}

Ship ship[1000];

void read_input()
{
  ll last = 0;
  cin >> l >> n;
  for (int i = 0; i < n; i++) {
    cin >> ship[i];
    last = max(last, ship[i].t);
  }

  for (int i = 0; i < n; i++) {
    ship[i].adjust(last, l);
  }
}

// returns true if x is covered by any interval.  Assumes interval is sorted
// lexicographically
//
// we can afford to do linear search
bool covered(const pii interval[], ll x)
{
  for (int i = 0; i < n; i++) {
    if (interval[i].first <= x && x <= interval[i].second)
      return true;
  }
  return false;
}

// find first a >= 0 that is not contained in any interval
ll find_first(pii interval[])
{
  sort(interval, interval+n);
  if (interval[0].first > 0) {
    return 0;
  }

  // all candidates are right after the end of an interval
  ll cand[1000];
  for (int i = 0; i < n; i++) {
    cand[i] = interval[i].second+1;
  }
  sort(cand, cand+n);
  for (int i = 0; i < n; i++) {
    if (cand[i] >= 0 && !covered(interval, cand[i])) {
      return cand[i];
    }
  }

  assert(false);
  return -1;
}

int main()
{
  read_input();

  pii interval[1000];
  for (int i = 0; i < n; i++) {
    interval[i] = ship[i].forbidden();
  }
  cout << find_first(interval) << endl;
  
  return 0;
}
