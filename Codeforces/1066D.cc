#include <bits/stdc++.h>

using namespace std;

// the described packing algorithm is greedy, but the question is whether
// we can pack more objects by throwing away some prefix set of objects.
//
// Notice that we will always be packing some suffix set of objects.  If
// we can pack the last k objects, you can also pack last k-1 objects.
// Similarly if you cannot pack the last k objects then you cannot pack the
// last k+1 objects either.
//
// In other words, we can do this by binary search on how many objects we
// can pack.

int n, m, k;
int a[200000];

bool check(int last)
{
  int curr_size = k;
  int boxes = 1;

  for (int i = n - last; i < n; i++) {
    if (a[i] <= curr_size) {
      curr_size -= a[i];
    } else {
      curr_size = k - a[i];
      boxes++;
    }
  }
  return boxes <= m;
  
}

int main()
{
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  if (check(n)) {
    cout << n << endl;
    return 0;
  }

  // cannot pack all of them
  int hi = n;
  int lo = 1;     // you can always pack 1: each object has size <= k

  while (hi - lo > 1) {
    int mid = (lo+hi)/2;
    if (check(mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  cout << lo << endl;

  

  return 0;
}
