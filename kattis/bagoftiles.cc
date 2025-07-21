#include <bits/stdc++.h>

using namespace std;

int binom[31][31];

int choose(int m, int n)
{
  if (n == m || n == 0) {
    return binom[m][n] = 1;
  }
  if (binom[m][n] > 0) {
    return binom[m][n];
  }

  return binom[m][n] = choose(m-1, n) + choose(m-1, n-1);
}

// ways[i][j] = number of ways to form the sum j, using subsets of size i
void count_ways(int tile[], int m, int ways[][10001])
{
  for (int mask = 0; mask < (1 << m); mask++) {
    int sum = 0;
    int size = 0;
    for (int i = 0; i < m; i++) {
      if (mask & (1 << i)) {
	sum += tile[i];
	size++;
      }
    }
    if (sum <= 10000) {
      ways[size][sum]++;
    }
  }
}

void solve()
{
  int m, tile[30];

  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> tile[i];
  }

  int n, t;
  cin >> n >> t;

  // total number of draws
  int total = choose(m, n);
  int win;
  
  // special case that needs to be handled
  if (n == 0) {
    if (t == 0) {
      win = 1;
    } else {
      win = 0;
    }
  } else {
    int ways1[31][10001], ways2[31][10001];
    for (int i = 0; i <= n; i++) {
      fill(ways1[i], ways1[i] + t + 1, 0);
      fill(ways2[i], ways2[i] + t + 1, 0);
    }
    
    count_ways(tile, m/2, ways1);
    count_ways(tile+m/2, m-m/2, ways2);

    // count the ones in each half
    win = ways1[n][t] + ways2[n][t];
    
    // count the ones across subsets:
    //
    for (int i1 = 1; i1 < n; i1++) {
      for (int j1 = 1; j1 < t; j1++) {
	win += ways1[i1][j1] * ways2[n-i1][t-j1];
      }
    }
  }

  int lose = total - win;
  
  cout << win << " : " << lose << endl;
}

int main()
{
  int g;
  cin >> g;

  for (int i = 1; i <= g; i++) {
    cout << "Game " << i << " -- ";
    solve();
  }

  return 0;
}
