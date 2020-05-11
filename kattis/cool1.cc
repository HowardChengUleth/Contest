#include <bits/stdc++.h>

using namespace std;
int N;
string prog;
bool grid[202][202];
int last[202][202][202];

int period(const string &s)
{
  int n = s.length();
  for (int p = 1; p <= n/2; p++) {
    if (n % p) continue;

    bool good = true;
    for (int j = p; j < n && good; j++) {
      good &= (s[j] == s[j % p]);
    }
    if (good) return p;
  }

  return s.length();
}

int main() {
  cin >> N >> prog;

  int r, c;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      char ch;
      cin >> ch;
      grid[i][j] = (ch != '#');
      if (ch == 'R') {
	r = i;
	c = j;
      }
    }
  }

  int t = 0;
  for (int i = 0; i < N+2; i++) {
    for (int j = 0; j < N+2; j++) {
      for (int k = 0; k < N+2; k++) {
	last[i][j][k] = -1;
      }
    }
  }

  string trail;
  int pl = prog.length();
  
  while (last[r][c][t % pl] < 0) {
    last[r][c][t % pl] = trail.length();
    int rr = r, cc = c;
    switch (prog[t % pl]) {
    case '^':
      rr--;
      break;
    case 'v':
      rr++;
      break;
    case '<':
      cc--;
      break;
    case '>':
      cc++;
      break;
    }
    if (grid[rr][cc]) {
      trail += prog[t % pl];
      r = rr;
      c = cc;
    }
    
    t++;
  }

  trail = trail.substr(last[r][c][t % pl]);

  if (trail == "") {
    cout << 1 << endl;
  } else {
    cout << period(trail) << endl;
  }
  return 0;
}
