#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

// idea: meet-in-the-middle
//
// Let rootP = floor(sqrt(P))
//
// Write L = a * rootP + b
// where 0 <= a <= P / rootP,
//       0 <= b < rootP
//
// Then B^L = N mod P is equivalent to
//
//   B^(a * rootP) = N * B^(P - 1 - b) mod P
//
// Look for a match with the smallest a, and then the smallest b


int fast_exp(int b, int n, int m)
{
  int res = 1;
  long long x = b;

  while (n > 0) {
    if (n & 0x01) {
      n--;
      res = (res * x) % m;
    } else {
      n >>= 1;
      x = (x * x) % m;
    }
  }

  return res;
}

int main(void)
{
  int P, B, N;
  while (cin >> P >> B >> N) {
    // build table of N*B^(P-1-b) for all b.  Use a map so it is easier
    // to lookup
    map<int, int> table;

    int rootP = (int)floor(sqrt(P));
    int maxb = min(rootP - 1, P - 1);

    // go backward so the smallest entry will be stored for each rhs
    // in case of duplication
    for (int b = maxb; b >= 0; b--) {
      int rhs = ((long long)N * fast_exp(B, P - 1 - b, P)) % P;
      table[rhs] = b;
    }

    bool found = false;
    for (int a = 0; a <= P / rootP && !found; a++) {
      int lhs = fast_exp(B, a * rootP, P);
      if (table.find(lhs) != table.end()) {
	int L = a * rootP + table[lhs];
	cout << L << endl;
	found = true;
      }
    }
    if (!found) {
      cout << "no solution" << endl;
    }
  }
  return 0;
}
