#include <cstdio>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

double D, L;					

double dist(double x1, double y1, double x2, double y2)
{
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double search(int xsi, int ysi, int xti, int yti, 
	      double xs, double ys, double xt, double yt,
	      map< pair<int, int>, double> &table)
{
  int xdiff, ydiff, mindiff, maxdiff;
  int i;
  double d = -1, t;

  xdiff = xti - xsi;
  ydiff = ysi - yti;
  mindiff = (xdiff < ydiff) ? xdiff : ydiff;
  maxdiff = (xdiff > ydiff) ? xdiff : ydiff;

  if (xsi == xti || ysi == yti) {
    return dist(xs, ys, xt - (xti-xsi)*2*L, yt + (ysi - yti)*2*L);
  }
  if (table.find(make_pair(xsi, ysi)) != table.end()) {
    return table[make_pair(xsi, ysi)];
  }

  if (xdiff > ydiff) {
    for (i = 1; i <= xdiff-mindiff+1; i++) {
      t = search(xsi+i, ysi-1, xti, yti, (xsi+i)*D+L, ysi*D-L, xt, yt, table)
	+ dist(xs, ys, (xsi+i)*D+L - i*2*L, ysi*D+L);
      if (d < 0 || t < d) {
	d = t;
      }
    }
  } else if (xdiff < ydiff) {
    for (i = 1; i <= ydiff-mindiff+1; i++) {
      t = search(xsi+1, ysi-i, xti, yti, (xsi+1)*D+L, (ysi-i+1)*D-L, xt, yt, 
		 table)
	+ dist(xs, ys, (xsi+1)*D-L, (ysi-i+1)*D-L + i*2*L);
      if (d < 0 || t < d) {
	d = t;
      }
    }

  } else {
    d = search(xsi+1, ysi-1, xti, yti, (xsi+1)*D+L, ysi*D-L, xt, yt, table) 
      + dist(xs, ys, (xsi+1)*D-L, ysi*D+L);
  }

  
  return table[make_pair(xsi, ysi)] = d;
}

int main(void)
{ 
  double xs, ys, xt, yt;
  int xsi, ysi, xti, yti;
  double swim, walk = 0.0;
  int xdiff, ydiff, mindiff, maxdiff;

  while (scanf("%lf %lf %lf %lf %lf %lf", &D, &L, &xs, &ys, &xt, &yt) == 6 &&
	 (D != 0 && L != 0 && xs != 0 && ys != 0 && xt != 0 && yt != 0)) {
    map< pair<int, int>, double > table;

    xsi = (int)floor(xs/D);
    ysi = (int)floor(ys/D);
    xti = (int)floor(xt/D);
    yti = (int)floor(yt/D);

    xdiff = xti - xsi;
    ydiff = ysi - yti;
    mindiff = (xdiff < ydiff) ? xdiff : ydiff;
    maxdiff = (xdiff > ydiff) ? xdiff : ydiff;
    swim = mindiff*2*L*sqrt(2.0) + (maxdiff-mindiff)*2*L;
    walk = search(xsi, ysi, xti, yti, xs, ys, xt, yt, table);

    printf("The gopher has to swim %.2f meters and walk %.2f meters.\n",
	   swim, walk);
  }

  return 0;
}
