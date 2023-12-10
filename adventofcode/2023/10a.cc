#include <bits/stdc++.h>

using namespace std;

vector<string> A;
int M, N;
int startr, startc;

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

int dist[200][200];

string pipe_str = "|-LJ7F";

string pipe_dir[256];
int dr[256], dc[256];

void trace(int r, int c, int d = 0)
{
  if (dist[r][c] != -1) {
    return;
  }
  dist[r][c] = d;

  bool done = false;
  for (auto dirc : pipe_dir[A[r][c]]) {
    int r2 = r + dr[dirc], c2 = c + dc[dirc];
    assert(inside(r2, c2));
    if (dist[r2][c2] == -1) {
      trace(r2, c2, d+1);
      done = true;
    }

    if (done) break;
  }
}


int main()
{
  pipe_dir['|'] = "NS";
  pipe_dir['-'] = "EW";
  pipe_dir['L'] = "NE";
  pipe_dir['J'] = "NW";
  pipe_dir['7'] = "SW";
  pipe_dir['F'] = "SE";

  dr['E'] = dr['W'] = dc['N'] = dc['S'] = 0;
  dc['E'] = 1;
  dc['W'] = -1;
  dr['N'] = -1;
  dr['S'] = 1;
  
  string str;
  while (getline(cin, str)) {
    A.push_back(str);
  }

  M = A.size();
  N = A[0].size();

  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (A[r][c] == 'S') {
	startr = r;
	startc = c;
      }
      dist[r][c] = -1;
    }
  }

  for (auto c : pipe_str) {
    bool good = true;
    auto dir_str = pipe_dir[c];
    for (auto dirc : dir_str) {
      int r2 = startr + dr[dirc], c2 = startc + dc[dirc];
      auto adjc = A[r2][c2];
      if (!inside(r2, c2) || adjc == '.') good = false;
      bool found = false;
      for (auto backc : pipe_dir[adjc]) {
	int r3 = r2 + dr[backc], c3 = c2 + dc[backc];
	found |= (r3 == startr && c3 == startc);
      }
      good &= found;
    }
    if (good) {
      A[startr][startc] = c;
      cout << "found " << c << endl;
      break;
    }
  }

  trace(startr, startc);

  int ans = 0;
  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      ans = max(dist[r][c], ans);
    }
  }

  cout << (ans+1)/2 << endl;
  
  return 0;
}
