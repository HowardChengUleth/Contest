#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

struct UnionFind
{
  vector<int> uf;
  UnionFind(int n) : uf(n) {
    for (int i = 0; i < n; i++) uf[i] = i;
  }
  
  int find(int x) {
    return (uf[x] == x) ? x : (uf[x] = find(uf[x]));
  }
  
  bool merge(int x, int y) {
    int res1 = find(x), res2 = find(y);
    if (res1 == res2) return false;
    uf[res2] = res1;
    return true;
  }
};

int L, W;
int N;
int X[100], Y[100];

const double EPS = 1e-8;

bool possible(double diameter)
{
  UnionFind uf(102);

  double r = diameter/2;

  for (int i = 0; i < N; i++) {
    if (Y[i] - diameter <= 0) {
      uf.merge(0, i+2);
    }
    if (Y[i] + diameter >= W) {
      uf.merge(1, i+2);
    }
    for (int j = i+1; j < N; j++) {
      int d2 = (X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]);
      if (d2 < diameter*diameter) {
	uf.merge(i+2, j+2);
      }
    }
  }

  return uf.find(0) != uf.find(1);
}

void solve(int id)
{
  cin >> L >> W;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i];
  }

  double lo = 0, hi = W;
  while (hi - lo > 1e-8) {
    double mid = (lo+hi)/2;
    if (possible(mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  cout << "Maximum size in test case " << id << " is "
       << fixed << setprecision(4) << lo << "." << endl;
}

int main()
{
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    solve(i);
  }
  return 0;
}
