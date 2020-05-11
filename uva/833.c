/* @JUDGE_ID: 1102NT 833 C "" */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct {
  double x, y;
} Point;

typedef struct {
  Point a, b;
} Line;

Line *line;
int NP;

#define EPSILON 1E-8

int intersect_line(Point a, Point b, Point c, Point d, Point *p)
{
  Point t;
  double r, s, denom, num1, num2;

  num1 = (a.y-c.y)*(d.x-c.x) - (a.x-c.x)*(d.y-c.y);
  num2 = (a.y-c.y)*(b.x-a.x) - (a.x-c.x)*(b.y-a.y);
  denom = (b.x-a.x)*(d.y-c.y) - (b.y-a.y)*(d.x-c.x);
  
  if (fabs(denom) >= EPSILON) {
    r = num1 / denom;
    s = num2 / denom;
    if (0-EPSILON <= r && r <= 1+EPSILON &&
	0-EPSILON <= s && s <= 1+EPSILON) {
      p->x = a.x + r*(b.x-a.x);
      p->y = a.y + r*(b.y-a.y);
      return 1;
    } else {
      return 0;
    }
  } else {
    if (fabs(num1) >= EPSILON) {
      return 0;
    } else {
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

void process(Point p)
{
  Line l;
  int i, best_i;
  Point best_p, temp_p;

  /* drop a line down */
  l.a = p;
  l.b.x = p.x; l.b.y = 0;

  /* look for intersection */
  best_i = -1;
  for (i = 0; i < NP; i++) {
    if (intersect_line(l.a, l.b, line[i].a, line[i].b, &temp_p)) {
      if (best_i == -1 || temp_p.y > best_p.y) {
	best_i = i;
	best_p = temp_p;
      }
    }
  }

  if (best_i == -1) {
    /* we are done */
    printf("%.0f\n", p.x);
    return;
  }

  /* drop from the lower end-point and recurse */
  p = line[best_i].a;
  if (p.y > line[best_i].b.y) {
    p = line[best_i].b;
  }
  p.y -= 0.2;   /* drop down just a little */
  process(p);
}

int main(void)
{
  int cases;
  int i;
  int NS;
  Point src;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d", &NP);
    line = malloc(NP*sizeof(*line));
    assert(line);
    for (i = 0; i < NP; i++) {
      scanf("%lf %lf %lf %lf", &(line[i].a.x), &(line[i].a.y),
	    &(line[i].b.x), &(line[i].b.y));
    }

    scanf("%d", &NS);
    for (i = 0; i < NS; i++) {
      scanf("%lf %lf", &src.x, &src.y);
      process(src);
    }

    free(line);
    if (cases) {
      printf("\n");
    }
  }
  return 0;
}
