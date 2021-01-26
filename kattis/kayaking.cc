#include <bits/stdc++.h>

using namespace std;

int num[3], s[3];
int c[50000];
int m;

struct Pair
{
  int i, j;

  Pair(int ii = 0, int jj = 0)
    : i{ii}, j{jj} { }
  
  bool operator<(const Pair &p) const
  {
    return s[i]+s[j] < s[p.i]+s[p.j];
  }
};

Pair p[9];

bool check(int v) {
  int k = m-1;
  int n[3];
  copy(num, num+3, n);
  
  for (int i = 0; i < 9; i++) {
    int p1 = p[i].i, p2 = p[i].j;
    bool good = (p1 == p2 && n[p1] >= 2) ||
      (p1 != p2 && n[p1] >= 1 && n[p2] >= 1);
    while (good && k >= 0 && c[k]*(s[p1]+s[p2]) >= v) {
      k--;
      n[p1]--;
      n[p2]--;
      good = (p1 == p2 && n[p1] >= 2) ||
	(p1 != p2 && n[p1] >= 1 && n[p2] >= 1);
    }
  }
  return k < 0;
}

int main()
{
  for (int i = 0; i < 3; i++) {
    cin >> num[i];
    m += num[i];
  }
  m /= 2;
  for (int i = 0; i < 3; i++) {
    cin >> s[i];
  }

  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }
  sort(c, c+m);
  
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      p[i*3+j] = Pair(i, j);
    }
  }
  sort(p, p+9);
  
  int lo = 0, hi = 1;
  while (check(hi)) {
    hi *= 2;
  }

  // lo = yes, hi = no
  while (hi - lo > 1) {
    int mid = (lo + hi) / 2;
    if (check(mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  cout << lo << endl;
  return 0;
}
