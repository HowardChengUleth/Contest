#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

pair<int,int> edge[10000*2];
int start[10000];

// minsum[i][j] = minimum sum for the subtree rooted at i, if color of i
//                is j.
const int MAX_COLOR = 14;

int minsum[10000][MAX_COLOR];
int n, m;

int compute(int v, int c, int parent = -1)
{
  if (minsum[v][c] >= 0) return minsum[v][c];

  int ans = c+1;
  for (int i = start[v]; i < m && edge[i].first == v; i++) {
    int w = edge[i].second;
    if (w == parent) continue;

    int branch = -1;
    for (int j = 0; j < MAX_COLOR; j++) {
      if (j == c) continue;
      int t = compute(w, j, v);
      if (branch < 0 || t < branch) {
	branch = t;
      }
    }
    ans += branch;
  }

  return minsum[v][c] = ans;
}

bool solve()
{
  cin >> n;
  if (!n) return false;

  m = 0;
  for (int i = 0; i < n; i++) {
    int from;
    cin >> from;
    cin.ignore(1);

    string line;
    getline(cin, line);
    istringstream iss(line);
    int to;
    while (iss >> to) {
      edge[m++] = make_pair(from, to);
      edge[m++] = make_pair(to, from);
    }
  }

  sort(edge, edge+m);
  fill(start, start+n, m);
  for (int i = 0; i < m; i++) {
    if (i == 0 || edge[i-1].first != edge[i].first) {
      start[edge[i].first] = i;
    }
  }

  for (int i = 0; i < n; i++) {
    fill(minsum[i], minsum[i]+MAX_COLOR, -1);
  }
  int ans = compute(0, 0);
  for (int c = 1; c < MAX_COLOR; c++) {
    ans = min(ans, compute(0, c));
  }
  
  cout << ans << endl;
  
  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}
