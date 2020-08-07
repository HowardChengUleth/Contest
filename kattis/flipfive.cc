#include <bits/stdc++.h>

using namespace std;

// idea is that there are really only 2^9 = 512 possible configurations, so
// we will use BFS to try each move and see what is the shortest path to the
// goal.  I am using a bitmask of 9 bits to represent the configuration, so
// each of the 9 possible flips can be represented as the XOR of an appropriate
// bit mask.

const int bm[9] = {
  11, 23, 38, 89, 186, 308, 200, 464, 416
};

void solve()
{
  int grid = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      char c;
      cin >> c;
      if (c == '*') {
	grid |= (1 << (i*3+j));
      }
    }
  }

  int dist[520];
  fill(dist, dist+520, -1);

  queue<int> q;
  q.push(grid);
  dist[grid] = 0;
  
  while (!q.empty()) {
    int curr = q.front();
    q.pop();

    for (int m = 0; m < 9; m++) {
      int next = bm[m] ^ curr;
      if (dist[next] < 0) {
	dist[next] = dist[curr] + 1;
	q.push(next);
      }
    }
  }

  cout << dist[0] << endl;
}

int main()
{
  int P;
  cin >> P;

  while (P--)
    solve();
  
  return 0;
}
