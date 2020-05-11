#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

struct Range {
  int rook, lo, hi;
};

#define MAX_ROOK 5000

Range xrange[MAX_ROOK], yrange[MAX_ROOK];
int x[MAX_ROOK], y[MAX_ROOK];
int n;

bool operator<(const Range &a, const Range &b)
{
  return a.lo < b.lo;
}

class Compare {
public:
  bool operator()(const Range &a, const Range &b)
  {
    return a.hi > b.hi;
  }
};

int main(void)
{
  cin >> n;
  while (n > 0) {
    int i, bad = 0;

    for (i = 0; i < n; i++) {
      xrange[i].rook = yrange[i].rook = i;
      cin >> xrange[i].lo >> yrange[i].lo >> xrange[i].hi >> yrange[i].hi;
    }
    sort(xrange, xrange+n);
    sort(yrange, yrange+n);
    
    int xi = 0, yi = 0;
    priority_queue< Range, vector<Range>, Compare > xq, yq;
    for (i = 1; i <= n && !bad; i++) {
      while (xi < n && xrange[xi].lo == i) {
	xq.push(xrange[xi++]);
      }
      while (yi < n && yrange[yi].lo == i) {
	yq.push(yrange[yi++]);
      }
      if (!xq.empty() && i <= xq.top().hi) {
	x[xq.top().rook] = i;
	xq.pop();
      } else {
	bad = 1;
      }
      if (!yq.empty() && i <= yq.top().hi) {
	y[yq.top().rook] = i;
	yq.pop();
      } else {
	bad = 1;
      }
    }
    if (bad) {
      printf("IMPOSSIBLE\n");
    } else {
      for (i = 0; i < n; i++) {
	printf("%d %d\n", x[i], y[i]);
      }
    }
    cin >> n;
  }
  return 0;
}
