#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef vector<string> vs;
typedef vector<vector<bool>> vvb;
typedef long long ll;
typedef pair<int,int> pii;

int M, N;
vs grid;

void read_grid()
{
  string s;
  while (getline(cin, s)) {
    grid.push_back(s);
  }
  M = grid.size();
  N = grid[0].length();
}

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

ll count_sides(vector<int> &v)
{
  sort(begin(v), end(v));

  int sides = v.size();
  for (int i = 1; i < v.size(); i++) {
    assert(v[i] > v[i-1]);
    if (v[i] == v[i-1]+1) {
      sides--;
    }
  }
  return sides;
}

ll score(int r, int c, vvb &marked)
{
  char type = grid[r][c];

  queue<pii> Q;
  Q.emplace(r, c);
  
  ll area = 0;

  // we key the horizontal edges as row 0, 1, ..., M
  //   the vector would collect all of the column coordinates
  //
  // we further separate horizontal edges as whether it is a top/bot
  //    boundary
  //
  // we key the vertical edges as column 0, 1, ..., N
  //   the vector would collect all of the row coordinates
  //
  // we further separate vertical edges as whether it is a left/right
  map<int,vector<int>> vert_left, vert_right, horiz_top, horiz_bot;
  

  while (!Q.empty()) {
    auto [curr_r, curr_c] = Q.front();
    Q.pop();
    bool first = !marked[curr_r][curr_c];
    marked[curr_r][curr_c] = true;

    if (first) {
      area++;
      for (int d = 0; d < 4; d++) {
	int r2 = curr_r + dr[d], c2 = curr_c + dc[d];
	if (!inside(r2, c2) || grid[r2][c2] != type) {
	  if (curr_c == c2) {
	    // horizontal boundary
	    int row = (r2 < curr_r) ? curr_r : curr_r + 1;
	    if (r2 < curr_r) {
	      horiz_top[row].push_back(curr_c);
	    } else {
	      horiz_bot[row].push_back(curr_c);
	    }
	  } else {
	    // vertical boundary
	    int col = (c2 < curr_c) ? curr_c : curr_c + 1;
	    if (c2 < curr_c) {
	      vert_left[col].push_back(curr_r);
	    } else {
	      vert_right[col].push_back(curr_r);
	    }
	  }
	}
	
	if (inside(r2, c2) && grid[r2][c2] == type && !marked[r2][c2]) {
	  Q.emplace(r2, c2);
	}
      }
    }
  }

  int sides = 0;
  for (int r = 0; r <= M; r++) {
    if (horiz_top.find(r) != horiz_top.end()) {
      sides += count_sides(horiz_top[r]);
    }
    if (horiz_bot.find(r) != horiz_bot.end()) {
      sides += count_sides(horiz_bot[r]);
    }
    
  }
  for (int c = 0; c <= N; c++) {
    if (vert_left.find(c) != vert_left.end()) {
      sides += count_sides(vert_left[c]);
    }
    if (vert_right.find(c) != vert_right.end()) {
      sides += count_sides(vert_right[c]);
    }
  }

  return area * sides;
}

int main()
{
  read_grid();

  vvb marked(M, vector<bool>(N, false));

  ll ans = 0;
  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (marked[r][c]) continue;
      ans += score(r, c, marked);
    }
  }

  cout << ans << endl;

  return 0;
}
