#include <bits/stdc++.h>

using namespace std;

int N, M;
string A[2000];
vector<vector<int>> label, psum;
vector<vector<bool>> int_sand;
map<int,int> treasure;

const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

bool inside(int r, int c)
{
  return 0 <= r && r < N && 0 <= c && c < M;
}

void DFS(int r, int c, int region)
{
  label[r][c] = region;
  for (int d = 0; d < 4; d++) {
    int r2 = r + dr[d], c2 = c + dc[d];
    if (!inside(r2, c2)) continue;
    if (A[r2][c2] == '0' || label[r2][c2] != -1) continue;
    DFS(r2, c2, region);
  }
}

int label_regions()
{
  label.resize(N, vector<int>(M, -1));
  int region = 0;
  for (int r = 0; r < N; r++) {
    for (int c = 0; c < M; c++) {
      if (A[r][c] != '0' && label[r][c] == -1) {
	DFS(r, c, region++);
      }
    }
  }

  return region;
}

void find_int_sand()
{
  int_sand.resize(N, vector<bool>(M, false));
  for (int r = 0; r < N; r++) {
    for (int c = 0; c < M; c++) {
      if (A[r][c] != '1') continue;
      bool interior = true;
      for (int d = 0; d < 4; d++) {
	int r2 = r + dr[d], c2 = c + dc[d];
       	interior &= (inside(r2, c2) && A[r2][c2] != '0');
      }
      int_sand[r][c] = interior;
    }
  }
}

void compute_psum()
{
  psum.resize(N, vector<int>(M, 0));

  psum[0][0] = int_sand[0][0];
  for (int c = 1; c < M; c++) {
    psum[0][c] = psum[0][c-1] + int_sand[0][c];
  }

  for (int r = 1; r < N; r++) {
    psum[r][0] = psum[r-1][0] + int_sand[r][0];
    for (int c = 1; c < M; c++) {
      psum[r][c] = psum[r-1][c] + psum[r][c-1] + int_sand[r][c]
	- psum[r-1][c-1];
    }
  }
}

bool square(int r, int c, int side)
{
  int r1 = r - side + 1, c1 = c - side + 1;

  int count = psum[r][c];
  if (r1 > 0) {
    count -= psum[r1-1][c];
  }
  if (c1 > 0) {
    count -= psum[r][c1-1];
  }
  if (r1 > 0 && c1 > 0) {
    count += psum[r1-1][c1-1];
  }

  return count == side*side;
  
}

int best_square(int r, int c)
{
  // lo = possible, hi = impossible
  int lo = 1, hi = min(r, c) + 1;

  if (square(r, c, hi)) {
    return hi*hi;
  }

  while (hi - lo > 1) {
    int mid = (lo + hi)/2;
    if (square(r, c, mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  return lo * lo;
}

int main()
{
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  int regions = label_regions();
  find_int_sand();
  compute_psum();

  for (int r = 0; r < N; r++) {
    for (int c = 0; c < M; c++) {
      if (!int_sand[r][c]) continue;
      int L = label[r][c];
      treasure[L] = max(treasure[L], best_square(r, c));
    }
  }

  int ans = 0;
  for (auto [ L, count ] : treasure) {
    ans += count * 10;
  }

  cout << ans << endl;
  
  return 0;
  
}
