#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct UnionFind
{
  vector<int> uf;
  UnionFind(int n) : uf(n) {
    for (int i = 0; i < n; i++) uf[i] = i;
  }
  
  int find(int x) {
    return (uf[x] == x) ? x : (uf[x] = find(uf[x]));
  }
  
  bool merge(int x, int y) {
    int res1 = find(x), res2 = find(y);
    if (res1 == res2) return false;
    uf[res2] = res1;
    return true;
  }
};


int P, R;

void solve()
{
  UnionFind uf(P);

  int ans = 0;
  for (int i = 0; i < R; i++) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    if (!uf.merge(a, b)) {
      ans++;
    }
  }
  
  cout << ans << endl;
}

int main()
{
  bool first = true;

  while (cin >> P >> R) {
    if (!first) cout << endl;
    solve();
    first = false;
  }

  return 0;
}
