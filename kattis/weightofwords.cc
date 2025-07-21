#include <bits/stdc++.h>

using namespace std;

// memo[L][W] = 0 if it is not possible to form a string of length L with
//                with weight W
//              1-26 if you can do it by starting the string with A-Z
//             -1 uninitialized

int memo[41][1001];

int f(int L, int W)
{
  int &ans = memo[L][W];

  if (ans >= 0) {
    return ans;
  }

  if (L == 1) {
    if (1 <= W && W <= 26) {
      return ans = W;
    } else {
      return ans = 0;
    }
  }
  
  for (int i = 1; i <= 26; i++) {
    if (i > W) continue;
    if (f(L-1, W-i)) {
      return ans = i;
    }
  }

  return ans = 0;
}

int main()
{
  int L, W;
  cin >> L >> W;

  for (int i = 0; i <= L; i++) {
    fill(memo[i], memo[i]+W+1, -1);
  }
  
  if (f(L, W)) {
    for (int i = L; i > 0; i--) {
      cout << char('a' + memo[i][W] - 1);
      W -= memo[i][W];
    }
    cout << endl;
  } else {
    cout << "impossible" << endl;
  }

  return 0;
}
