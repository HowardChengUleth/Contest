#include <iostream>
#include <cstring>
#include <algorithm>
#include <cassert>

using namespace std;
#define IN(i) ((i)>0 && (i)<= n)

const int maxn=40+10;
const int w[4][4]={{-3,-1,4,-4},{1,3,4,-4},{1,-1,4,-4},{1,-1,4,-4}};
const int limit=100000;
int p[maxn], map[maxn][maxn], n, test, ans;

void prepare()
{
  // figure out taxicab distance between squares
  for (int i = 1; i <= 40; i++) {
    for (int j = 1; j <= 40; j++) {
      map[i][j]=(i==j)?0:limit;
    }
  }
   
  for (int i = 1; i <= 40; i++) {
    for (int j = 0; j < 4; j++) {
      if (i+ w[i%4][j] > 0 && i + w[i%4][j] <= 40) {
	map[i][i+w[i%4][j]] = map[i+w[i%4][j]][i] = 1;
      }
    }
  }

  for (int k = 1; k <= 40; ++k) {
    for (int i = 1; i <= 40; ++i) {
      for (int j = 1; j <= 40; ++j) {
	map[i][j] = min(map[i][j], map[i][k]+map[k][j]);
      }
    }
  }
}

bool dfs(int pos, int c, int dep, int last)
{
  if (!c) return true;
  
  // cut off if depth + distance to goal >= ans
  if (c+dep > ans) return false;
  
  int np, nc;
  for (int i = 0; i < 4; i++) {
    np = pos + w[pos%4][i];
    
    // move unless it was exactly the parent
    if (IN(np) && (np != last)) {
      nc = c - map[np][p[np]] + map[pos][p[np]];
      p[pos] = p[np];
      p[np] = 1;
      if (dfs(np, nc, dep+1, pos)) return true;
      p[np] = p[pos]; p[pos]=1;
    }
  }
  return false;
}

void work()
{
    int k = 0, pos;
    for (int i = 1; i <= n; i++) {
        k += map[i][p[i]];
        if (p[i] == 1) pos = i;      // position of king
    }
    k -= map[pos][1];
    cout << "Set " << ++test << ":" << endl;

    // iterative deepening
    for (ans = 0; ; ans++) {
      if (dfs(pos, k, 0, -1)) {
	cout << ans << endl;
	return;
      }
    }
}

int main()
{
  prepare();
  while (cin >> n && n) {
    for(int i = 1; i <= n; ++i) {
      cin >> p[i];
    }
    work();
  }
  return 0;
}
