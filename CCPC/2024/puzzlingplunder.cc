#include <bits/stdc++.h>
#include <cassert>

using namespace std;

struct Puzzle
{
  Puzzle() = default;
  Puzzle(int hh, int ww)
    : h{hh}, w{ww}, r0{hh-1}, c0{ww-1}
  {
    int k = 1;
    for (int r = 0; r < h; r++) {
      for (int c = 0; c < w; c++) {
	A[r][c] = k++;
      }
    }
    A[r0][c0] = 0;
  }
  
  bool move(int dir) {
    assert(0 <= dir && dir < 4);
    int r2 = r0 + dr[dir], c2 = c0 + dc[dir];
    if (!inside(r2, c2)) return false;
    swap(A[r0][c0], A[r2][c2]);
    r0 = r2;
    c0 = c2;
    return true;
  }

  void unmove(int dir) {
    bool res = move((dir+2) % 4);
    
    if (!res) {
      cout << "dir = " << dir << endl;
      cout << "h, w = " << h << ' ' << w << endl;
      cout << "r0, c0 = " << r0 << ' ' << c0 << endl;
    }
    assert(res);
  }

  int height() const {
    return h;
  }
  int width() const {
    return w;
  }

  bool operator==(const Puzzle &p) const
  {
    if (!(h == p.h && w == p.w && r0 == p.r0 && c0 == p.c0))
      return false;
    for (int r = 0; r < h; r++) {
      for (int c = 0; c < w; c++) {
	if (A[r][c] != p.A[r][c]) {
	  return false;
	}
      }
    }
    return true;
  }
  
  int h, w;
  int A[8][8];
  int r0, c0;

  const int dr[4] = { -1, 0, 1, 0 };
  const int dc[4] = { 0, -1, 0, 1 };

  bool inside(int r, int c) const
  {
    return 0 <= r && r < h && 0 <= c && c < w;
  }
};

template <>
struct std::hash<Puzzle>
{
  size_t operator()(const Puzzle& p) const
  {
    size_t result = 0;
    for (int r = 0; r < p.h; r++) {
      for (int c = 0; c < p.w; c++) {
	result <<= 1;
	result ^= hash<int>()(p.A[r][c]);
      }
    }
    return result;
  }
};


istream &operator>>(istream &is, Puzzle &p)
{
  is >> p.h >> p.w;
  for (int r = 0; r < p.h; r++) {
    for (int c = 0; c < p.w; c++) {
      cin >> p.A[r][c];
      if (p.A[r][c] == 0) {
	p.r0 = r;
	p.c0 = c;
      }
    }
  }
  return is;
}

ostream &operator<<(ostream &os, const Puzzle &p)
{
  for (int r = 0; r < p.h; r++) {
    for (int c = 0; c < p.w; c++) {
      os << setw(3) << p.A[r][c];
    }
    os << endl;
  }
  return os;
}

int bidir_search(Puzzle start, Puzzle goal)
{
  if (start == goal) {
    return 0;
  }

  unordered_map<Puzzle, int> dist1, dist2;
  queue<Puzzle> q1, q2;

  q1.push(start);
  dist1[start] = 0;
  q2.push(goal);
  dist2[goal] = 0;

  // expand from start
  for (int curr_d = 0; curr_d <= 10; curr_d++) {
    while (!q1.empty() && dist1[q1.front()] == curr_d) {
      auto p = q1.front();
      q1.pop();

      for (int dir = 0; dir < 4; dir++) {
	if (!p.move(dir)) continue;
	if (dist2.find(p) != dist2.end()) {
	  return curr_d + 1 + dist2[p];
	}
	if (dist1.find(p) == dist1.end()) {
	  dist1[p] = curr_d+1;
	  q1.push(p);
	}
	p.unmove(dir);
      }
    }
  }

  while (!q2.empty()) {
    auto p = q2.front();
    q2.pop();
    int curr_d = dist2[p];
    if (curr_d > 10) break;
    
    for (int dir = 0; dir < 4; dir++) {
      if (!p.move(dir)) continue;
      if (dist1.find(p) != dist1.end()) {
	return curr_d + 1 + dist1[p];
      }
      if (dist2.find(p) == dist2.end()) {
	dist2[p] = curr_d+1;
	q2.push(p);
      }
      p.unmove(dir);
    }
  }

  return -1;
}

void solve()
{
  Puzzle start;
  cin >> start;
  Puzzle goal(start.height(), start.width());

  cout << bidir_search(start, goal) << endl;
}

int main()
{
  int N;
  cin >> N;
  while (N--) {
    solve();
  }
  return 0;
}
