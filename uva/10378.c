/* @JUDGE_ID: 1102NT 10378 C "" */

/* use de Moivre's identity:

   cos(theta/n) + i sin(theta/n) = (cos(theta) + i sin(theta))^(1/n)

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EPS 1e-8

typedef struct {
  double x, y;
} Point;

int cmp(const void *a, const void *b)
{
  Point *p1 = (Point *)a, *p2 = (Point *)b;

  if (fabs(p1->x - p2->x) > EPS) {
    return (p1->x > p2->x) ? -1 : 1;
  } else if (fabs(p1->y - p2->y) > EPS) {
    return (p1->y > p2->y) ? -1 : 1;
  } else {
    return 0;
  }
}

int main(void)
{
  int case_no = 1;
  int a, b, n;
  double r, theta, pi;
  int i;
  Point p[100];

  pi = acos(-1);

  while (scanf("%d%di %d", &a, &b, &n) == 3) {
    printf("Case %d:\n", case_no++);
    r = sqrt(a*a+b*b);
    theta = atan2(b, a);

    r = pow(r, 1.0/n);

    for (i = 0; i < n; i++) {
      p[i].x = r * cos(theta/n);
      p[i].y = r * sin(theta/n);
      theta += 2*pi;
    }
    
    qsort(p, n, sizeof(*p), cmp);

    for (i = 0; i < n; i++) {
      if (fabs(p[i].x) < 0.0005) p[i].x = 0;
      if (fabs(p[i].y) < 0.0005) p[i].y = 0;
      printf("%.3f%s%.3fi\n", p[i].x, ((p[i].y >= 0) ? "+" : ""),
	     p[i].y);
    }

    printf("\n");
  }

  return 0;
}
