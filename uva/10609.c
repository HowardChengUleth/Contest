/* @JUDGE_ID: 1102NT 10609 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-8
#define COSPART 0.5000000000
#define SINPART (sqrtl(3.0)/2.0)

typedef struct
{
      long double x, y;
} point;

int cmp(const void *x, const void *y)
{
  point p1 = *(point *)x, p2 = *(point *)y;

  if (fabsl(p1.x - p2.x) < EPSILON) {
    if (p1.y > p2.y) {
      return 1;
    } else if (p1.y < p2.y) {
      return -1;
    } else {
      return 0;
    }
  } else {
    return (p1.x > p2.x) ? 1 : -1;
  }
}

int count;

void draw(point a, point b, point *A, long double t)
{
   long double length;
   point c, d, e, diff;

   c.x = a.x + (b.x - a.x) / 4.0;
   c.y = a.y + (b.y - a.y) / 4.0;
   d.x = b.x + (a.x - b.x) / 4.0;
   d.y = b.y + (a.y - b.y) / 4.0;

   length = sqrtl((d.x - c.x) * (d.x - c.x) + (d.y - c.y) * (d.y - c.y));
   if (length < t && fabsl(length - t) >= EPSILON) return;

   diff.x = d.x - c.x;
   diff.y = d.y - c.y;
   e.x = diff.x * COSPART - diff.y * SINPART + c.x;
   e.y = diff.y * COSPART + diff.x * SINPART + c.y;

   A[count++] = c;
   A[count++] = d;
   A[count++] = e;

   draw(c, e, A, t);
   draw(e, d, A, t);
}

int main()
{
   point A[100000];
   int c = 0, i;
   long double t, length;
   point a, b;

   while (1)
   {
      scanf("%Lf %Lf %Lf %Lf %Lf", &a.x, &a.y, &b.x, &b.y, &t);
      if (t < 1.0) break;
      
      printf("Case %d:\n", ++c);

      count = 0;

      length = sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
      if (length > t || fabsl(length - t) < EPSILON) {
      
	A[count++] = a;
	A[count++] = b;

	draw(a, b, A, t);
      }
      qsort(A, count, sizeof(point), cmp);

      printf("%d\n", count);
      
      for (i = 0; i < count; ++i)
        printf("%.5Lf %.5Lf\n", A[i].x, A[i].y);
   }
   
   return 0;
}
