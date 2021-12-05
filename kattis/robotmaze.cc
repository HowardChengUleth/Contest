#include <bits/stdc++.h>

using namespace std;

const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

int a, b;

struct Node
{
  int r, c, d, s;

  Node(int rr, int cc, int dd, int ss)
    : r{rr}, c{cc}, d{dd}, s{ss} { }
};

int dist[1000][1000][4][3];

void solve()
{
  cin >> a >> b;

  string A[1000];
  for (int i = 0; i < a; i++) {
    cin >> A[i];
  }


  for (int r = 0; r < a; r++) {
    for (int c = 0; c < b; c++) {
      for (int d = 0; d < 4; d++) {
	for (int s = 0; s < 3; s++) {
	  dist[r][c][d][s] = -1;
	}
      }
    }
  }

  int dest_r, dest_c;
  queue<Node> q;
  
  for (int r = 0; r < a; r++) {
    for (int c = 0; c < b; c++) {
      if (A[r][c] == 'B') continue;
      else if (A[r][c] == 'R') {
	for (int d = 0; d < 4; d++) {
	  q.emplace(r, c, d, 0);
	  dist[r][c][d][0] = 0;
	}
      } else if (A[r][c] == 'D') {
	dest_r = r;
	dest_c = c;
      }
    }
  }

  while (!q.empty()) {
    Node curr = q.front();
    q.pop();

    int r = curr.r, c = curr.c, d = curr.d, s = curr.s;
    int curr_d = dist[r][c][d][s];

    if (r == dest_r && c == dest_c) {
      cout << curr_d << endl;
      return;
    }
    
    int r2 = r + dr[d], c2 = c + dc[d];
    if (s < 2 && 0 <= r2 && r2 < a && 0 <= c2 && c2 < b &&
	A[r2][c2] != 'B') {
      if (dist[r2][c2][d][s+1] == -1) {
	q.emplace(r2, c2, d, s+1);
	dist[r2][c2][d][s+1] = curr_d + 1;
      }
      if (dist[r2][c2][(d+1)%4][0] == -1) {
	q.emplace(r2, c2, (d+1)%4, 0);
	dist[r2][c2][(d+1)%4][0] = curr_d + 1;
      }
      if (dist[r2][c2][(d+3)%4][0] == -1) {
	q.emplace(r2, c2, (d+3)%4, 0);
	dist[r2][c2][(d+3)%4][0] = curr_d + 1;
      }
    }
  }

  cout << -1 << endl;
}


int main()
{
  int k;
  cin >> k;
  while (k--) {
    solve();
  }

  return 0;
}
