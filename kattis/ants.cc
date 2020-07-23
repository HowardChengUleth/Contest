#include <bits/stdc++.h>

using namespace std;

// the idea is that we don't have to actually worry about ants bumping into
// each other, because we can pretend that they just pass through each other
// and the times are not affected (because we don't have to know which ant is
// the last one to reach the end).  So for each ant we just have to try sending
// the ant both ways and see how long they take to fall off

int main(void)
{
  int l, n;
  int dist;
  int cases;
  int earliest, latest;
  int t1, t2;

  cin >> cases;
  while (cases-- > 0) {
    cin >> l >> n;
    earliest = latest = -1;
    while (n-- > 0) {
      cin >> dist;
      t1 = min(dist, l-dist);
      t2 = max(dist, l-dist);
      earliest = max(earliest, t1);
      latest = max(latest, t2);
    }
    cout << earliest << ' ' << latest << endl;
  }
  
  return 0;
}
