#include <iostream>
#include <algorithm>

using namespace std;

int v;
bool adj[200][200];
int label[200];

bool dfs(int i, int &countp, int &countn, int tag)
{
  if (label[i]) {
    return label[i] == tag;
  }

  label[i] = tag;
  if (tag > 0) {
    countp++;
  } else {
    countn++;
  }

  bool good = true;
  for (int j = 0; j < v; j++) {
    if (adj[i][j]) {
      good &= dfs(j, countp, countn, -tag);
    }
  }

  return good;
}

void solve()
{
  int e;
  cin >> v >> e;
  for (int i = 0; i < v; i++) {
    fill(adj[i], adj[i]+v, false);
  }

  while (e--) {
    int f, t;
    cin >> f >> t;
    adj[f][t] = adj[t][f] = true;
  }

  bool good = true;
  int ans = 0;

  fill(label, label+v, 0);
  for (int i = 0; i < v && good; i++) {
    if (label[i]) continue;
    int countp = 0, countn = 0;
    good &= dfs(i, countp, countn, 1);

    // handle special case for isolated vertices
    if (countp + countn == 1) {
      ans++;
    } else {
      ans += min(countp, countn);
    }
  }
  
  if (good) {
    cout << ans << endl;
  } else {
    cout << -1 << endl;
  }
}

int main(void)
{
  int T;
  cin >> T;

  while (T--) {
    solve();
  }

  return 0;
}
