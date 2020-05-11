#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

int N, M;
int D[51][51];
int P;
int store[12];
int save[12];

int table[4096][13];

int compute(int subset, int end)
{
  if (table[subset][end] != INT_MIN) {
    return table[subset][end];
  }

  if (subset == (1 << (end-1))) {
    return table[subset][end] = save[end-1] - D[0][store[end-1]];
  }

  for (int i = 1; i <= P; i++) {
    if (!(subset & (1 << (i-1)))) continue;
    if (i == end) continue;
    int t = compute(subset-(1 << (end-1)), i)
      + save[end-1] - D[store[i-1]][store[end-1]];
    table[subset][end] = max(table[subset][end], t);
  }
  return table[subset][end];
}

void solve()
{
  cin >> N >> M;
  for (int i = 0; i <= N; i++) {
    fill(D[i], D[i]+N+1, INT_MAX);
    D[i][i] = 0;
  }
  while (M--) {
    int u, v, d, c;
    char dot;
    cin >> u >> v >> d >> dot >> c;
    int t = d*100+c;
    D[u][v] = D[v][u] = min(D[u][v], t);
  }
  cin >> P;
  for (int i = 0; i < P; i++) {
    int d, c;
    char dot;
    cin >> store[i] >> d >> dot >> c;
    save[i] = d*100+c;
  }

  for (int k = 0; k <= N; k++) {
    for (int i = 0; i <= N; i++) {
      if (D[i][k] == INT_MAX) continue;
      for (int j = 0; j <= N; j++) {
	if (D[k][j] < INT_MAX) {
	  int t = D[i][k] + D[k][j];
	  D[i][j] = min(t, D[i][j]);
	}
      }
    }
  }

  for (int i = 1; i < (1 << P); i++) {
    fill(table[i]+1, table[i]+P+1, INT_MIN);
  }
  table[0][0] = 0;

  int best = INT_MIN;
  for (int subset = 1; subset < (1 << P); subset++) {
    for (int i = 1; i <= P; i++) {
      if (subset & (1 << (i-1))) {
	best = max(best, compute(subset, i) - D[store[i-1]][0]);
      }
    }
  }

  if (best <= 0) {
    cout << "Don't leave the house" << endl;
  } else {
    cout << "Daniel can save $" << best/100 << "." << setw(2) << setfill('0')
	 << best%100 << endl;
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
