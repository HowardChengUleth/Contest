#include <bits/stdc++.h>

using namespace std;

// bestval[c][k] = the maximum value you can get if the capacity of knapsack is
//                 c and considering only objects 0, 1, ..., k-1
// chosen[c][k] = is object k-1 chosen for the max value
int bestval[2001][2001];
bool chosen[2001][2001];

int C, n;
int w[2000], v[2000];

int f(int c, int k)
{
  if (bestval[c][k] >= 0)
    return bestval[c][k];

  // no more object
  if (k == 0) return bestval[c][k] = 0;

  // try not using object
  bestval[c][k] = f(c, k-1);
  chosen[c][k] = false;
  
  // try using it
  if (w[k-1] <= c) {
    int t = f(c-w[k-1], k-1) + v[k-1];
    if (t > bestval[c][k]) {
      bestval[c][k] = t;
      chosen[c][k] = true;
    }
  }

  return bestval[c][k];
}

void trace(int c, int k, vector<int> &v)
{
  if (k == 0) return;

  if (chosen[c][k]) {
    v.push_back(k-1);
    trace(c-w[k-1], k-1, v);
  } else {
    trace(c, k-1, v);
  }

}

bool solve()
{
  if (!(cin >> C >> n))
    return false;

  for (int i = 0; i < n; i++) {
    cin >> v[i] >> w[i];
  }

  for (int i = 0; i <= C; i++) {
    fill(bestval[i], bestval[i]+n+1, -1);
  }

  f(C, n);

  vector<int> soln;
  trace(C, n, soln);

  cout << soln.size() << endl;
  for (auto x : soln) {
    cout << x << ' ';
  }
  cout << endl;

  return true;
}

int main()
{
  while (solve())
    ;

  return 0;
}
