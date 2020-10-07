#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[20];
int dp[1000001];

// first person wins or not?
bool f(int s) {
  int& x = dp[s];
  if (x >= 0) return x;
  if (s == 0) return x = false;

  for (int i = 0; i < m; i++) {
    if (s - a[i] >= 0) {
      if (!f(s-a[i])) {
	return x = true;
      }
    }
  }
  return x = false;
}

int main() {
  while (cin >> n >> m) {
    for (int i = 0; i < m; i++) cin >> a[i];
    for (int i = 0; i <= n; i++)
      dp[i] = -1;
    if (f(n)) cout << "Stan wins" << endl;
    else cout << "Ollie wins" << endl;
  }
}

