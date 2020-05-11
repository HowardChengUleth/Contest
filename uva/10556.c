/* @JUDGE_ID: 1102NT 10556 C "" */

#include <stdio.h>
#include <math.h>

typedef struct {
  int x, y;
} Point;

/* counterclockwise, clockwise, or undefined */
enum {CCW, CW, CNEITHER};

int ccw(Point a, Point b, Point c)
{
  int dx1 = b.x - a.x;
  int dx2 = c.x - b.x;
  int dy1 = b.y - a.y;
  int dy2 = c.y - b.y;
  int t1 = dy2 * dx1;
  int t2 = dy1 * dx2;

  if (t1 == t2) {
    if (dx1 * dx2 < 0 || dy1 * dy2 < 0) {
      if (dx1*dx1 + dy1*dy1 >= dx2*dx2 + dy2*dy2) {
        return CNEITHER;
      } else {
        return CW;
      }
    } else {
      return CCW;
    }
  } else if (t1 > t2) {
    return CCW;
  } else {
    return CW;
  }
}

void read_poly(int n, Point *poly)
{
  int i;
  
  for (i = 0; i < n; i++) {
    scanf("%d %d", &(poly[i].x), &(poly[i].y));
  }
  poly[n] = poly[0];
  poly[n+1] = poly[1];
}

/* Note: we are really computing the cosine of the angle */
void compute(int n, Point *poly, double *angle, int *orient, double *dist)
{
  int dx1, dy1, dx2, dy2;
  int i;
  
  for (i = 0; i < n; i++) {
    /* i-th angle is angle formed by points i, i+1, i+2 */
    dx1 = poly[i].x - poly[i+1].x;  dy1 = poly[i].y - poly[i+1].y;
    dx2 = poly[i+2].x - poly[i+1].x; dy2 = poly[i+2].y - poly[i+1].y;
    angle[i] = (dx1*dx2+dy1*dy2)/sqrt(dx1*dx1+dy1*dy1)/sqrt(dx2*dx2+dy2*dy2);
    orient[i] = ccw(poly[i], poly[i+1], poly[i+2]);
    dist[i] = sqrt((poly[i+1].x-poly[i].x)*(poly[i+1].x-poly[i].x) +
      (poly[i+1].y-poly[i].y)*(poly[i+1].y-poly[i].y));
  }
}

int main(void)
{
  Point poly1[12], poly2[12];
  double angle1[10], angle2[10];
  int orient1[10], orient2[10];
  double dist1[10], dist2[10], ratio;
  int n, i;
  int similar;

  while (scanf("%d", &n) != EOF && n > 0) {
    read_poly(n, poly1);
    read_poly(n, poly2);

    compute(n, poly1, angle1, orient1, dist1);
    compute(n, poly2, angle2, orient2, dist2);
    ratio = dist2[0]/dist1[0];

    similar = 1;
    for (i = 0; i < n && similar; i++) {
      similar = (orient1[i] == orient2[i] && 
		 fabs(angle1[i]-angle2[i]) < 1e-8 &&
		 fabs(dist1[i]*ratio-dist2[i]) < 1e-8);
      
    }

    printf("%s\n", (similar) ? "similar" : "dissimilar");
  }
  
  return 0;
}
