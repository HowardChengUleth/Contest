#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int m, n;
int bad[24];

ll memo[30][64];

// mask: bits 0-2 = next column which ones are sticking out
//       bits 3-5 = 2nd next column which ones are sticking out
ll f(int col, int mask)
{
  if (col >= m) {
    return (!mask) ? 1 : 0;
  }
  
  if (memo[col][mask] >= 0)
    return memo[col][mask];
  
  // look for lowest row that needs to be covered
  ll ans = 0;
  bool found = false;
  for (int i = 0; i < 3 && !found; i++) {
    if (mask & (1 << i)) continue;         // already covered
    if (bad[col] & (1 << i)) continue;     // don't need to cover
    found = true;

    // try putting 1x1
    ans += f(col, mask | (1 << i));

    // try putting 1x2 vertically
    if (i+1 < 3 && !(mask & (1 << (i+1))) && !(bad[col] & (1 << (i+1)))) {
      ans += f(col, mask | (3 << i));
    }

    // try putting 1x2 horizontally
    if (col+1 < m && !(mask & (1 << (i+3))) && !(bad[col+1] & (1 << i))) {
      ans += f(col, mask | (9 << i));
    }
  }

  // there is nothing that needs to be covered in this column
  if (!found) {
    return memo[col][mask] = f(col+1, mask >> 3);
  }
  
  return memo[col][mask] = ans;
}

int main()
{
  cin >> m >> n;
  fill(bad, bad+m, 0);
  for (int i = 0; i < n; i++) {
    double x, y;
    cin >> x >> y;
    int xx = (int)x, yy = (int)y;
    bad[xx] |= (1 << yy);
  }

  for (int i = 0; i < 30; i++)
    fill(memo[i], memo[i]+64, -1);

  cout << f(0, 0) << endl;
  
  return 0;
}
