#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1000;
const int MAX_C = 10000;

int N, C;
vector<ll> a;

ll ceil(ll a, ll b)
{
  return (a + (b-1)) / b;
}

int main()
{
  cin >> N >> C;

  a.resize(N);
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }
  sort(begin(a), end(a));

  // possible[i][j] = true if you can make sum j with i pillows
  bool possible[100][MAX_C+1] = { false };
  possible[0][0] = true;
  ll div = 1;
  int k = 1;
  
  while (a[0] > div) {
    for (int c = 0; c <= C; c++) {
      for (int i = 0; i < N; i++) {
	ll val = ceil(a[i], div);
	if (val > c) break;
	if (possible[k-1][c-val]) {
	  possible[k][c] = true;
	  break;
	}
      }
    }
    if (possible[k][C]) {
      cout << "YES" << endl;
      return 0;
    }
    div *= 2;
    k++;
  }
  
  for (int c = 0; c <= C; c++) {
    if (possible[k-1][c]) {
      cout << "YES" << endl;
      return 0;
    }
  }

  cout << "NO" << endl;
  
  return 0;
}
