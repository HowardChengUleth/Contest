#include <bits/stdc++.h>

using namespace std;

//
// If you write the coordinates in base 3 notation, it will look like
// 0.120120012 (each digit is 0, 1, or 2).
//
// If the i-th digit is 1, then it is in the "middle" chunk at the i-th step
// and will be removed.  The only exception is when the number terminates
// with a 1.  e.g. 0.00210000....  In that case it is on the boundary of the
// hole being removed.
//
// Also, for the point to be removed at the i-th step, it has to be removed
// in at least two of the coordinates, so we check against xy, xz, and yz.


// get base 3 expansion of the "decimal" part
vector<int> base3(int L, int n, int d)
{
  vector<int> v(L);
  
  for (int i = 0; i < L; i++) {
    n *= 3;
    v[i] = n / d;
    n %= d;
  }

  // fake the last entry to indicate zero or nonzero termination
  v.push_back(n);
  
  return v;
}

// are the rest of the expansion 0
bool zeros(const vector<int> &v, int s)
{
  int n = v.size();
  return count(begin(v)+s, end(v), 0) == n-s;
}

int main()
{
  int L, xn, xd, yn, yd, zn, zd;
  cin >> L >> xn >> xd >> yn >> yd >> zn >> zd;

  auto xv = base3(L, xn, xd);
  auto yv = base3(L, yn, yd);
  auto zv = base3(L, zn, zd);

  bool good = true;
  for (int i = 0; i < L; i++) {
    if (xv[i] == yv[i] && xv[i] == 1) {
      if (!zeros(xv, i+1) && !zeros(yv, i+1)) {
	good = false;
      }
    }

    if (xv[i] == zv[i] && xv[i] == 1) {
      if (!zeros(xv, i+1) && !zeros(zv, i+1)) {
	good = false;
      }
    }

    if (yv[i] == zv[i] && yv[i] == 1) {
      if (!zeros(yv, i+1) && !zeros(zv, i+1)) {
	good = false;
      }
    }
  }

  cout << (good ? 1 : 0) << endl;
  
  return 0;
}
