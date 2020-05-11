/* @JUDGE_ID: 1102NT 143 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* how close to call equal */
#define EPSILON 1E-8

typedef struct {
  double x, y;
} Point;

/* returns 1 if intersect at a point, 0 if not, -1 if the lines coincide */
int intersect_line(Point a, Point b, Point c, Point d, Point *p)
{
  Point t;
  double r, s;
  double denom, num1, num2;

  /* the judge's input can have c == d! */
  if (c.x == d.x && c.y == d.y) {
    if (c.y == a.y) {
      p->x = c.x;
      p->y = c.y;
      return 1;
    } else {
      return 0;
    }
  }

  num1 = (a.y - c.y)*(d.x - c.x) - (a.x - c.x)*(d.y - c.y);
  num2 = (a.y - c.y)*(b.x - a.x) - (a.x - c.x)*(b.y - a.y);
  denom = (b.x - a.x)*(d.y - c.y) - (b.y - a.y)*(d.x - c.x);

  if (fabs(denom) >= EPSILON) {
    r = num1 / denom;
    s = num2 / denom;
    if (0-EPSILON <= r && r <= 1+EPSILON && 
        0-EPSILON <= s && s <= 1+EPSILON) {
      /* always do this part if we are interested in lines instead */
      /* of line segments                                          */
      p->x = a.x + r*(b.x - a.x);
      p->y = a.y + r*(b.y - a.y);
      return 1;
    } else {
      return 0;
    }
  } else {
    if (fabs(num1) >= EPSILON) {
      return 0;
    } else {
      /* I am not using "fuzzy comparisons" here, because the comparisons */
      /* are based on the input, not some derived quantities.  You may    */
      /* want to change that if the input points are computed somehow.    */

      /* two lines are the "same".  See if they overlap */
      if (a.x > b.x || (a.x == b.x && a.y > b.y)) {
        t = a;
        a = b;
        b = t;
      }
      if (c.x > d.x || (c.x == d.x && c.y > d.y)) {
        t = c;
        c = d;
        d = t;
      }
      if (a.x == b.x) {
        /* vertical lines */
        if (b.y == c.y) {
          *p = b;
          return 1;
        } else if (a.y == d.y) {
          *p = a;
          return 1;
        } else if (b.y < c.y || d.y < a.y) {
          return 0;
        } else {
          return -1;
        }
      } else {
        if (b.x == c.x) {
          *p = b;
          return 1;
        } else if (a.x == d.x) {
          *p = a;
          return 1;
        } else if (b.x < c.x || d.x < a.x) {
          return 0;
        } else {
          return -1;
        }
      }

      return -1;
    }
  }
}

int main(void)
{
  Point a, b, c;
  Point h1, h2;
  Point p[3];
  int count, num, i, j;
  double x1, x2;

  while (scanf("%lf %lf %lf %lf %lf %lf",
         &a.x, &a.y, &b.x, &b.y, &c.x, &c.y) == 6) {
    if (a.x == 0 && a.y == 0 && b.x == 0 && b.y == 0 && c.x == 0 && c.y == 0) {
      break;
    }
    count = 0;
    for (i = 1; i <= 99; i++) {
      h1.x = 0;  h1.y = i;
      h2.x = 100; h2.y = i;
      num = 0;
      if (intersect_line(h1, h2, a, b, p+num) == 1) {
	num++;
      }
      if (intersect_line(h1, h2, a, c, p+num) == 1) {
	num++;
      }
      if (intersect_line(h1, h2, b, c, p+num) == 1) {
	num++;
      }

      if (num == 0) {
	continue;
      }

      x1 = x2 = p[0].x;
      for (j = 0; j < num; j++) {
	if (p[j].x < x1) {
	  x1 = p[j].x;
	}
	if (p[j].x > x2) {
	  x2 = p[j].x;
	}
      }
      
      /* first round to 8 digits */
      x1 = floor(x1/EPSILON+0.5)*EPSILON;
      x2 = floor(x2/EPSILON+0.5)*EPSILON;
      
      x1 = ceil(x1);
      x2 = floor(x2);
      if (x1 < 1) {
	x1 = 1;
      }
      if (x2 > 99) {
	x2 = 99;
      }
      
      /*      printf("i = %d, x1 = %d, x2 = %d\n", i, (int)x1, (int)x2); */
      if (x2 >= x1) {
	count += (int)x2 - (int)x1 + 1;
      }
    }
    printf("%4d\n", count);

  }

  return 0;
}
