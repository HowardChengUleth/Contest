#include <iostream>
#include <iomanip>

using namespace std;

double table[21][21];

double compute(double p[], int n, int r)
{
  if (r > n || r < 0) {
    return 0;
  } else if (n == 0) {
    return 1;
  }

  if (table[n][r] >= 0) {
    return table[n][r];
  }

  // choose p[n-1]
  double ans = 0.0;
  ans += p[n-1] * compute(p, n-1, r-1);

  // don't choose it
  ans += (1 - p[n-1]) * compute(p, n-1, r);
  
  return table[n][r] = ans;
}

bool solve(int id)
{
  int n, r;
  double p[20];

  cin >> n >> r;
  if (!n && !r) return false;
  for (int i = 0; i < n; i++) {
    cin >> p[i];
  }

  cout << "Case " << id << ":" << endl;

  for (int i = 0; i <= 20; i++) {
    for (int j = 0; j <= 20; j++) {
      table[i][j] = -1;
    }
  }
  double total = compute(p, n, r);

  for (int i = 0; i < n; i++) {
    swap(p[i], p[n-1]);
    for (int s = 0; s <= 20; s++) {
      for (int t = 0; t <= 20; t++) {
	table[s][t] = -1;
      }
    }

    double ans = p[n-1]*compute(p, n-1, r-1) / total;
    cout << fixed << setprecision(6) << ans << endl;
    swap(p[i], p[n-1]);
  }
  
  return true;
}

int main()
{
  int id = 1;
  while (solve(id++))
    ;
  return 0;
}
