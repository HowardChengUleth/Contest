#include <bits/stdc++.h>

using namespace std;

int n, m;

struct Tool
{
  int type, w, u;

  bool operator<(const Tool &t) const
  {
    return type < t.type;
  }

  void read()
  {
    cin >> type >> w >> u;
  }
};

Tool tool[1000];

bool init[1001][1001];
int memo[1001][1001];

// max utility for tools[start..n-1] using weight exactly w
// "forbid" is a type that cannot be used next
int f(int start, int w)
{
  if (start == n) {
    return (w == 0) ? 0 : -1;
  }

  if (init[start][w]) {
    return memo[start][w];
  }

  int ans1 = 0, ans2 = 0;
  
  // try not using the tool
  ans1 = max(ans1, f(start+1, w));

  // use the tool
  int w2 = w - tool[start].w;
  if (w2 >= 0) {
    int t = tool[start].type;

    int start2 = start+1;
    while (t % 2 == 0 && start2 < n && tool[start2].type/2 == t/2) {
      // multiuse tool
      start2++;
    }
      
    int val = f(start2, w2);
    if (val >= 0) {
      ans2 = tool[start].u + val;
    }
  }

  init[start][w] = true;
  return memo[start][w] = max(ans1, ans2);
}

int main()
{
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    tool[i].read();
  }
  sort(tool, tool+n);

  int ans = 0;
  for (int w = 0; w <= m; w++) {
    ans = max(ans, f(0, w));
  }

  cout << ans << endl;

  return 0;
}
