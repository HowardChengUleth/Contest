#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>

using namespace std;

double D, L;					

double dist(double x1, double y1, double x2, double y2)
{
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double compute(int xdiff, int ydiff, double xs, double ys, double xt, double yt)
{
  /* table[x][y] = min walking distance to destination if we were to start
     at the upper left corner of dry land (x,y).  The piece of dry land
     immediately to the SE of (xs,ys) is (0,0), and the piece containing
     (xt,yt) is (xdiff-1,ydiff-1).  In other words, to get to (x,y) the
     gopher has to cross x+1 vertical ditches and y+1 horizontal ditches  */
  
  double table[300][300];
  
  /* convert (xs,ys) and (xt,yt) to coordinates within the dry land, with
     (0,0) being the upper left corner */
  xs -= (int)(floor(xs / D) * D + L);
  ys -= (int)(floor(ys / D) * D + L);
  xt -= (int)(floor(xt / D) * D + L);
  yt -= (int)(floor(yt / D) * D + L);
  ys = D-2*L - ys;
  yt = D-2*L - yt;
  
  /* base case: if x == xdiff-1, we can just go vertically */
  for (int y = 0; y < ydiff && xdiff >= 1; y++) {
    table[xdiff-1][y] = hypot(xt, yt + (D-2*L)*(ydiff-1-y));
  }
  /* base case: if y == ydiff-1, we can just go horizontally */
  for (int x = 0; x < xdiff && ydiff >= 1; x++) {
    table[x][ydiff-1] = hypot(xt + (D-2*L)*(xdiff-1-x), yt);
  }
  
  /* normal case, compute backwards */
  for (int x = xdiff-2; x >= 0; x--) {
    for (int y = 0; y < ydiff-1; y++) {
      table[x][y] = -1;
      if (xdiff - x > ydiff - y) continue;   /* will never use because
						ydiff >= xdiff */
      if (x > y) continue;                   /* we cannot cross horizontal
                                                ditch without also crossing
                                                vertical ditch */
      
      /* try all places to cross to the next x coordinate of dry land */
      for (int y2 = y+1; ydiff - y2 >= xdiff - x - 1 ; y2++) {
	assert(table[x+1][y2] >= 0);
	double temp = hypot(D-2*L, (D-2*L)*(y2-y)) + table[x+1][y2];
	if (table[x][y] == -1 || temp < table[x][y]) {
	  table[x][y] = temp;
	}
      }
    }
  }

  /* now try to figure out the best place to cross for a vertical ditch
     for the very first time */
  double best = -1;
  for (int y2 = 0; ydiff - y2 >= xdiff; y2++) {
    assert(table[0][y2] >= 0);
    double temp = hypot(D-2*L-xs, D-2*L-ys + y2*(D-2*L)) + table[0][y2];
    if (best == -1 || temp < best) {
      best = temp;
    }
  }
  
  return best;
  
}

int main(void)
{ 
  double xs, ys, xt, yt;

  while (cin >> D >> L >> xs >> ys >> xt >> yt && D != 0) {

    /* if m*D+L <= x <= (m+1)*D-L, then

          m+L/D <= x/D <= m+1-L/D

       But L+L < D => 0 < L/D < 1/2, so

          m = floor(x/D)
    */
    
    int xsi = (int)floor(xs/D);
    int ysi = (int)floor(ys/D);
    int xti = (int)floor(xt/D);
    int yti = (int)floor(yt/D);

    int xdiff = xti - xsi;
    int ydiff = ysi - yti;

    /* must swim diagonally as much as possible, then make up the rest
       by vertical swims */
    double swim = xdiff*2*L*sqrt(2.0) + (ydiff-xdiff)*2*L;

    double walk = compute(xdiff, ydiff, xs, ys, xt, yt);

    cout << "The gopher has to swim " << fixed << setprecision(2) << swim
	 << " meters and walk " << walk << " meters." << endl;
  }

  return 0;
}
