#include <bits/stdc++.h>

using namespace std;

int N;
pair<int,int> p[1000];
int y[1000];

const int INF = 10000;

bool possible(int maxD)
{
  // try all possible x+y's as the bounding box
  for (int i = 0; i < N; i++) {
    int yy = y[i];

    // keep track of all of the ones that are not in the box
    int minx = INF, miny = INF, maxx = -INF, maxy = -INF;
    for (int j = 0; j < N; j++) {
      int x = p[j].first, y = p[j].second;
      if (!(p[0].first <= x && x <= p[0].first + maxD &&
	    yy <= y && y <= yy+maxD)) {
	minx = min(minx, x);
	miny = min(miny, y);
	maxx = max(maxx, x);
	maxy = max(maxy, y);
      }
    }
    if ((maxx - minx) <= maxD && (maxy - miny) <= maxD) {
      return true;
    }
  }
  return false;

}


int main()
{
  cin >> N;

  // rotate coordinates by 45 degrees
  for (int i = 0; i < N; i++) {
    int xx, yy;
    cin >> xx >> yy;
    p[i] = make_pair(xx - yy, xx + yy);
    y[i] = xx+yy;
  }
  sort(p, p+N);
  sort(y, y+N);

  int lo = -1, hi = INF;
  while (lo+1 != hi) {
    int mid = (lo+hi)/2;
    if (possible(mid)) {
      hi = mid;
    } else {
      lo = mid;
    }
  }
  cout << hi << endl;
  
  return 0;
}
