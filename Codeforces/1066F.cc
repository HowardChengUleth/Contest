#include <bits/stdc++.h>

using namespace std;

// we have to go one level at a time.  For each level, it is optimal to visit
// all the key points from left to right or right to left, never backtracking.
//
// So we can do this as a DP, where at each level we figure out what is the
// minimum cost to get to that level, travel through that level and end up
// there.

typedef long long ll;
typedef pair<ll,ll> pii;
map<int, vector<pii>> level;
vector<ll> total;
vector<vector<pii>> endp;

bool cmp(const pii &p1, const pii &p2)
{
  if (p1.first != p2.first) {
    return p1.first < p2.first;
  }
  return p1.second > p2.second;
}

// key = (level, first/last 0/1)
map<pii,ll> memo;

ll dist(pii p1, pii p2)
{
  return abs(p1.first-p2.first) + abs(p1.second-p2.second);
}

ll f(int lvl, int dir)
{
  if (lvl == 0) {
    return 0;
  }
  
  if (memo.find(pii(lvl, dir)) != memo.end()) {
    return memo[pii(lvl, dir)];
  }

  return memo[pii(lvl, dir)] = total[lvl] + 
    min(f(lvl-1, 0) + dist(endp[lvl-1][0], endp[lvl][1-dir]),
	f(lvl-1, 1) + dist(endp[lvl-1][1], endp[lvl][1-dir]));
}


int main()
{
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    ll x, y;
    cin >> x >> y;
    level[max(x,y)].emplace_back(x,y);
  }

  // add an artificial level at the start
  level[0].emplace_back(0,0);

  int curr = 0;
  for (auto p : level) {
    auto &v = p.second;
    total.resize(curr+1);
    total[curr] = 0;
    sort(begin(v), end(v), cmp);
    for (int i = 1; i < v.size(); i++) {
      total[curr] += dist(v[i-1], v[i]);
    }
    endp.resize(curr+1);
    endp[curr].push_back(v.front());
    endp[curr].push_back(v.back());
    curr++;
  }

  cout << min(f(curr-1,0), f(curr-1,1)) << endl;
  
  return 0;
}
