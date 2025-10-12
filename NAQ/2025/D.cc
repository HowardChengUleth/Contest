#include <bits/stdc++.h>

using namespace std;

const int di[] = { -1, 0, 1, 0 };
const int dj[] = { 0, 1, 0, -1 };

int r, c;
vector<string> G;

bool visited[50][50][4] = { false };

bool inside(int i, int j)
{
  return 0 <= i && i < r && 0 <= j && j < c;
}

void doit(int i, int j, int dir)
{
  while (true) {
    visited[i][j][dir] = true;

    // choice 1
    int next_dir = (dir + 3) % 4;
    int next_i = i + di[next_dir];
    int next_j = j + dj[next_dir];
    if (inside(next_i, next_j) && G[next_i][next_j] == '0') {
      goto next;
    }
    
    // choice 2
    next_dir = dir;
    next_i = i + di[next_dir];
    next_j = j + dj[next_dir];
    if (inside(next_i, next_j) && G[next_i][next_j] == '0') {
      goto next;
    }

    // choice 3
    next_dir = (dir + 1) % 4;
    next_i = i;
    next_j = j;

  next:
    i = next_i;
    j = next_j;
    dir = next_dir;
    if (visited[i][j][dir]) {
      break;
    }
  }
}

int main()
{
  cin >> r >> c;
  G.resize(r);

  int istart, jstart, iend, jend;

  cin >> istart >> jstart;
  cin >> iend >> jend;

  istart--;
  jstart--;
  iend--;
  jend--;
  
  for (auto &s : G) {
    cin >> s;
  }

  doit(istart, jstart, 1);

  int ans = 0;
  for (int d = 0; d < 4; d++) {
    if (visited[iend][jend][d]) {
      ans = 1;
    }
  }
  cout << ans << endl;
  
  return 0;
}
