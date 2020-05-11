#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int table[301][301];
bool init[301][301];
int val1[40], val2[40];
int m, S;

int compute(int v1, int v2)
{
  if (v1 < 0 || v2 < 0) {
    return -1;
  }
  if (init[v1][v2]) {
    return table[v1][v2];
  }

  for (int i = 0; i < m; i++) {
    int t = compute(v1 - val1[i], v2 - val2[i]);
    if (t >= 0) {
      if (table[v1][v2] == -1 || t+1 < table[v1][v2]) {
	table[v1][v2] = t+1;
      }
    }
  }
  init[v1][v2] = true;
  return table[v1][v2];
}

void solve()
{
  cin >> m >> S;

  for (int i = 0; i <= S; i++) {
    fill(table[i], table[i]+S+1, -1);
    fill(init[i], init[i]+S+1, false);
  }
  table[0][0] = 0;
  init[0][0] = true;

  for (int i = 0; i < m; i++) {
    cin >> val1[i] >> val2[i];
  }

  int ans = -1;
  for (int v1 = 0; v1 <= S; v1++) {
    int v2 = (int)floor(sqrt(S*S - v1*v1));
    while (v2*v2 < S*S - v1*v1) {
      v2++;
    }
    if (v2*v2 != S*S - v1*v1) continue;
    int t = compute(v1, v2);
    if (t < 0) continue;
    if (ans == -1 || t < ans) {
      ans = t;
    }
  }

  if (ans < 0) {
    cout << "not possible" << endl;
  } else {
    cout << ans << endl;
  }
}

int main(void)
{
  int n;
  cin >> n;
  while (n--) {
    solve();
  }

  return 0;
}
