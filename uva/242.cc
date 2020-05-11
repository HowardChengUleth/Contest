/* @JUDGE_ID: 1102NT 242 C++ "" */

#include <iostream>
#include <algorithm>
#include <cassert>
#include <iomanip>

using namespace std;

class Denomination {
  int n, v[100];

public:
  int &operator[](int i) { return v[i]; }
  int coverage(int S);
  bool operator<(const Denomination &d) {
    if (n != d.n) return (n > d.n);
    return (v[n-1] > d.v[n-1]);
  }

  friend istream &operator>>(istream &is, Denomination &d);
  friend ostream &operator<<(ostream &os, Denomination &d);
};

int Denomination::coverage(int S)
{
  int best[1002];
  int i, j, t;

  fill(best, best+1002, -1);
  best[0] = 0;
  for (i = 1; i <= 1001; i++) {
    for (j = 0; j < n && v[j] <= i; j++) {
      t = best[i - v[j]];
      if (t >= 0 && t <= S-1 && (best[i] < 0 || t+1 < best[i])) {
	best[i] = t+1;
      }
    }
    if (best[i] < 0) {
      return i-1;
    }
  }
  assert(0);
  return -1;
}

istream &operator>>(istream &is, Denomination &d)
{
  int i;
  is >> d.n;
  for (i = 0; i < d.n; i++) {
    is >> d[i];
  }
  return is;
}

ostream &operator<<(ostream &os, Denomination &d)
{
  int i;
  for (i = 0; i < d.n; i++) {
    os << setw(3) << d[i];
    //    if (i < d.n-1) {
    //      os << setw(3);
    //    }
  }
  return os;
}

int main(void)
{
  int S, N;
  Denomination denom[10];
  int coverage[10];
  int max_coverage, best_i;
  
  while (cin >> S && S > 0) {
    cin >> N;
    for (int i = 0; i < N; i++) {
      cin >> denom[i];
      coverage[i] = denom[i].coverage(S);
    }
    max_coverage = *max_element(coverage, coverage+N);
    cout << "max coverage =" << setw(4) << max_coverage << " :";
    best_i = -1;
    for (int i = 0; i < N; i++) {
      if (coverage[i] == max_coverage &&
	  (best_i == -1 || denom[best_i] < denom[i])) {
	best_i = i;
      }
    }
    cout << denom[best_i] << endl;
  }
  return 0;
}
