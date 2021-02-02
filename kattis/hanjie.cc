#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int r, c;

vi read_hint()
{
  vi v;
  
  int k;
  cin >> k;
  while (k--) {
    int a;
    cin >> a;
    v.push_back(a);
  }
  return v;
}

vi genhint(const vi &v)
{
  vi h;

  int n = v.size();
  int j;
  for (int i = 0; i < n; i = j) {
    for (j = i+1; j < n && v[i] == v[j]; j++)
      ;
    if (v[i]) {
      h.push_back(j-i);
    }
  }
  return h;
}

// possibilities indexed by hints
map<vi, vvi> poss;
vvi row, col;
vvi grid;

int solve(int ri)
{
  if (ri >= r) {
    for (int j = 0; j < c; j++) {
      vi v(r);
      for (int i = 0; i < r; i++) {
	v[i] = grid[i][j];
      }
      if (genhint(v) != col[j]) {
	return 0;
      }
    }
    return 1;
  }
  
  int ans = 0;

  for (auto v : poss[row[ri]]) {
    copy(begin(v), end(v), begin(grid[ri]));
    ans += solve(ri+1);
  }
  return ans;
}

int main()
{
  cin >> r >> c;

  grid.resize(r);
  for (auto &v : grid) {
    v.resize(c);
  }
  
  for (int i = 0; i < r; i++) {
    row.push_back(read_hint());
  }
  for (int i = 0; i < c; i++) {
    col.push_back(read_hint());
  }

  for (int m = 0; m < (1 << c); m++) {
    vi v(c);
    for (int i = 0; i < c; i++) {
      v[i] = (m & (1 << i)) ? 1 : 0;
    }
    auto h = genhint(v);
    poss[h].push_back(v);
  }
  
  cout << solve(0) << endl;
  
  return 0;
}
