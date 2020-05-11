#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

typedef unsigned long long ull;

// n1[n][d] = number of n-digit numbers starting with digit d
//            if d = 0, it counts all numbers with fewer than n
//            digits.
ull n1[20][10];

// n2[n] = number of numbers with exactly n digits (not counting
//         those with leading 0)
ull n2[20];

void init()
{
  for (int i = 0; i < 10; i++) {
    n1[1][i] = (i != 0 && i != 4) ? 1 : 0;
  }

  for (int n = 2; n <= 20; n++) {
    for (int d = 0; d < 10; d++) {
      if (d == 4) continue;
      n1[n][d] = (d) ? 1 : 0;      // account for d0...0
      for (int d2 = 0; d2 < 10; d2++) {
	if (d == 1 && d2 == 3) continue;
	n1[n][d] += n1[n-1][d2];
      }
    }
  }
  n1[1][0] = 1;   // hack for later on when we want to look at
                  // d0, d00, d000, ...
  
  n2[0] = 0;
  for (int n = 1; n <= 20; n++) {
    n2[n] = 0;
    for (int d = 1; d < 10; d++) {
      n2[n] += n1[n][d];
    }
  }
}

void find(ull &N, int &n, int &d, int prevn = -1, int prevd = -1)
{
  if (prevd != -1) {
    if (N == 1) {
      // it must be the trailing 0 case
      n = 1;
      d = 0;
      return;
    }
    N--;
  }
  
  n = -1;
  ull total = 0;
  ull prev = 0;
  // figure out how many digits
  for (int nn = 1; nn <= 20; nn++) {
    total += n2[nn];
    if (total >= N) {
      N -= prev;
      n = nn;
      break;
    }
    prev = total;
  }
  assert(n > 0);

  // figure out starting digit
  total = 0;
  prev = 0;
  for (int dd = 1; dd < 10; dd++) {
    if (dd == 4) continue;
    if (prevn == n+1 && prevd == 1 && dd == 3) continue;
    total += n1[n][dd];
    if (total >= N) {
      N -= prev;
      d = dd;
      return;
    }
    prev = total;
  }
}


void solve(ull N)
{
  int prevn, prevd;
  int n, d;

  prevn = prevd = -1;
  do {
    find(N, n, d, prevn, prevd);
    if (prevn >= 0) {
      for (int i = 0; i < prevn - n - 1; i++) {
	cout << '0';
      }
    }
    cout << d;
    prevn = n;
    prevd = d;
  } while (N > 0 && n > 1);

  for (int i = 0; i < prevn - 1; i++) {
    cout << '0';
  }
  
  cout << endl;
}

int main()
{
  init();

  ull N;
  while (cin >> N) {
    solve(N);
  }
  
  return 0;
}
