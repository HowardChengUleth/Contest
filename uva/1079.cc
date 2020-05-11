#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

int n;
double a[8], b[8];

bool possible(int order[], double mid)
{
  double last = a[order[0]];
  for (int i = 1; i < n; i++) {
    double next = last + mid;
    next = max(next, a[order[i]]);
    if (next > b[order[i]]) {
      return false;
    }
    last = next;
  }
  return true;
}

bool solve(int id)
{
  cin >> n;
  if (!n) return false;
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
    a[i] *= 60;
    b[i] *= 60;
  }

  double lo = 0;
  double hi = 1440*60;
  while (hi - lo > 1e-3) {
    bool done = false;
    double mid = lo + (hi-lo)/2;
    int order[8] = {0,1,2,3,4,5,6,7};
    do {
      done |= possible(order, mid);
    } while (!done && next_permutation(order, order+n));
    if (done) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  int sec = floor(lo+0.5);
  cout << "Case " << id << ": " << sec/60 << ":"
       << setfill('0') << setw(2) << sec%60 << endl;
  return true;
}

int main()
{
  int id = 1;
  while (solve(id++))
    ;

  return 0;
}
