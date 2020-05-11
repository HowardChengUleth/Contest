/* @JUDGE_ID: 1102NT 10553 C "" */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

char dirname[32][10] = {
  "N", "NbE", "NNE", "NEbN", "NE", "NEbE",
  "ENE", "EbN", "E", "EbS", "ESE", "SEbE", "SE",
  "SEbS", "SSE", "SbE", "S", "SbW", "SSW", "SWbS",
  "SW", "SWbW", "WSW", "WbS", "W", "WbN", "WNW",
  "NWbW", "NW", "NWbN", "NNW", "NbW"
};

int dirs[1000];
int pace[1000];

int n;

int find_dirs(char *name)
{
  int i;
  for (i = 0; i < 32; i++) {
    if (!strcmp(dirname[i], name)) {
      return i;
    }
  }
  assert(0);
}

double dist_line(double ax, double ay, double bx, double by, 
		 double cx, double cy)
{
  double L2, s;

  L2 = (bx-ax)*(bx-ax)+(by-ay)*(by-ay);
  assert(L2 > 0);
  s = ((ay-cy)*(bx-ax)-(ax-cx)*(by-ay)) / L2;

  return fabs(s*sqrt(L2));
}

double project(double ax, double ay, double bx, double by,
	       double cx, double cy)
{
  double vx, vy, wx, wy;

  vx = bx-ax; vy = by-ay;
  wx = cx-ax; wy = cy-ay;
  return (vx*wx+vy*wy)/(vx*vx+vy*vy);
}

int main(void)
{
  char buffer[10];
  double angle;
  double tx, ty, x, y, x2, y2, theta;
  int i;
  double pi, d, d2, t;

  pi = atan(1)*4;

  while (scanf("%d", &n) == 1 && n > 0) {
    for (i = 0; i < n; i++) {
      scanf("%s", buffer);
      dirs[i] = find_dirs(buffer);
      scanf("%d", pace+i);
    }
    scanf("%lf", &angle);
    angle = angle*2*pi/360.0;
    
    /* figure out the treasure */
    tx = ty = 0.0;
    for (i = 0; i < n; i++) {
      theta = (2*pi/32.0)*dirs[i]+angle;
      theta = pi/2 - theta;
      tx += pace[i]*cos(theta);
      ty += pace[i]*sin(theta);
    }

    /* now do it again and find the distance */
    d = sqrt(tx*tx+ty*ty);
    x = y = 0.0;
    for (i = 0; i < n; i++) {
      theta = (2*pi/32.0)*dirs[i];
      theta = pi/2 - theta;
      x2 = x + pace[i]*cos(theta);
      y2 = y + pace[i]*sin(theta);
      d2 = sqrt((tx-x2)*(tx-x2) + (ty-y2)*(ty-y2));
      if (d2 < d) {
	d = d2;
      }

      /* what if it's in between? */
      d2 = dist_line(x,y,x2,y2,tx,ty);
      t = project(x,y,x2,y2,tx,ty);
      if (-1e-8 <= t && t <= 1.0+1e-8 && d2 < d) {
	d = d2;
      }

      x = x2;
      y = y2;
    }
    printf("%.2f\n", d);
  }

  return 0;
}
