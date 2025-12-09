#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int M, N;

typedef pair<int64_t,int64_t> pii;

vector<pii> red;
vector<int64_t> rlist, clist;
map<int64_t,int> r_index, c_index;
vector<string> grid;

void compress_coord()
{
  for (auto [r,c] : red) {
    rlist.push_back(r);
    clist.push_back(c);
  }
  
  sort(begin(rlist), end(rlist));
  sort(begin(clist), end(clist));
  rlist.erase(unique(begin(rlist), end(rlist)), end(rlist));
  clist.erase(unique(begin(clist), end(clist)), end(clist));

  for (int i = 0; i < rlist.size(); i++) {
    r_index[rlist[i]] = i+1;
  }
  for (int i = 0; i < clist.size(); i++) {
    c_index[clist[i]] = i+1;
  }

}

void fill_grid()
{
  M = rlist.size();
  N = clist.size();
  grid.resize(M+2, string(N+2, '.'));

  cout << "M, N = " << M << ' ' << N << endl;
  
  for (int i = 0; i < red.size(); i++) {
    int j = (i+1) % red.size();

    int rs = r_index[red[i].first], re = r_index[red[j].first];
    int cs = c_index[red[i].second], ce = c_index[red[j].second];

    if (rs > re) swap(rs, re);
    if (cs > ce) swap(cs, ce);

    for (int r = rs; r <= re; r++) {
      for (int c = cs; c <= ce; c++) {
	grid[r][c] = '#';
      }
    }
  }

  queue<pii> Q;
  Q.emplace(0, 0);
  while (!Q.empty()) {
    auto [r,c] = Q.front();
    Q.pop();
    if (grid[r][c] != '.') continue; 
    grid[r][c] = '!';
    for (int r2 = r-1; r2 <= r+1; r2++) {
      for (int c2 = c-1; c2 <= c+1; c2++) {
	if (0 <= r2 && r2 < M+2 && 0 <= c2 && c2 < N+2 && grid[r2][c2] == '.') {
	  Q.emplace(r2, c2);
	}
      }
    }
  }

  for (int r = 0; r < M; r++) {
    replace(begin(grid[r]), end(grid[r]), '.', '#');
  }
}

int main()
{
  string line;

  while (getline(cin, line)) {
    replace(begin(line), end(line), ',', ' ');
    istringstream iss(line);
    int x, y;
    iss >> x >> y;
    red.emplace_back(y, x);
  }

  compress_coord();
  fill_grid();

  vector<vector<int>> csum(M+2, vector<int>(N+2, 0));
  for (int r = 1; r <= M; r++) {
    for (int c = 1; c <= N; c++) {
      csum[r][c] = csum[r-1][c] + csum[r][c-1] - csum[r-1][c-1] +
	(grid[r][c] == '#');
    }
  }

  int64_t ans = 0;
  for (int i = 0; i < red.size(); i++) {
    for (int j = i+1; j < red.size(); j++) {
      int rs = r_index[red[i].first];
      int cs = c_index[red[i].second];
      int re = r_index[red[j].first];
      int ce = c_index[red[j].second];

      if (rs > re) swap(rs, re);
      if (cs > ce) swap(cs, ce);
      
      int count = csum[re][ce] - csum[rs-1][ce] - csum[re][cs-1] +
	csum[rs-1][cs-1];
      if (count == (re-rs+1) * (ce-cs+1)) {
	int64_t dr = rlist[re-1] - rlist[rs-1] + 1;
	int64_t dc = clist[ce-1] - clist[cs-1] + 1;
	int64_t area = dr*dc;
	ans = max(ans, area);
      }
    }
  }

  cout << ans << endl;
  return 0;
}
