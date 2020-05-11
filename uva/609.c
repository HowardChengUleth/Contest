/* @JUDGE_ID: 1102NT 609 C "" */

/*
 * Solution to "Metal Cutting"
 *
 * Author: Howard Cheng
 * Date: Nov 10, 1998
 *
 * Comment: Brute force with minor pruning
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>

#define MAX_POLY 10
#define EPS 1E-8

typedef struct {
  double x, y;
} Point;

Point poly[MAX_POLY];
int npoly;
double min_cut;
Point cut_u[MAX_POLY], cut_v[MAX_POLY];
int cuts[MAX_POLY];

double dist(Point a, Point b)
{
  double dx = a.x - b.x;
  double dy = a.y - b.y;

  return sqrt(dx*dx + dy*dy);
}

/* returns 1 if intersect at a point, 0 if not, -1 if they are coincident */
int intersect(Point a, Point b, Point c, Point d, Point *p, double *r)
{
  double denom, num1, num2, s;

  assert((a.x != b.x || a.y != b.y) && (c.x != d.x || c.y != d.y));

  num1 = (a.y - c.y)*(d.x - c.x) - (a.x - c.x)*(d.y - c.y);
  num2 = (a.y - c.y)*(b.x - a.x) - (a.x - c.x)*(b.y - a.y);
  denom = (b.x - a.x)*(d.y - c.y) - (b.y - a.y)*(d.x - c.x);


  if (fabs(denom) > EPS) {
    *r = num1 / denom;
    s = num2 / denom;
    if (-EPS <= s && s <= 1.0+EPS) {
      p->x = a.x + (*r)*(b.x - a.x);
      p->y = a.y + (*r)*(b.y - a.y);
      return 1;
    } else {
      return 0;
    }
  } else {
    if (fabs(num1) > EPS) {
      return 0;
    } else {
      assert(0);
      return -1;
    }
  }
}

int coincident(Point a, Point b, Point *outside, int noutside)
{
  Point res, c, d;
  double r;

  int i;

  for (i = 0; i < noutside; i++) {
    c = outside[i];
    d = outside[(i+1) % noutside];
    if (intersect(a, b, c, d, &res, &r) == -1) {
      return 1;
    }
  }
  return 0;
}

Point find_lower(Point a, Point b, Point *outside, int noutside, int *index)
{
  Point res, c, d;
  double r;
  int i;

  for (i = 0; i < noutside; i++) {
    c = outside[i];
    d = outside[(i+1) % noutside];
    if (intersect(a, b, c, d, &res, &r) == 1 && r <= EPS) {
      *index = i;
      return res;
    }
  }
  assert(0);
}

Point find_upper(Point a, Point b, Point *outside, int noutside, int *index)
{
  Point res, c, d;
  double r;
  int i, t;

  for (i = 0; i < noutside; i++) {
    c = outside[i];
    d = outside[(i+1) % noutside];
    if ((t = intersect(a, b, c, d, &res, &r)) == 1 && r >= 1.0-EPS) {
      *index = i;
      return res;
    }
  }
  assert(0);
}

int get_outside(Point *newoutside, Point u, Point v, 
		int u_index, int v_index, Point *outside, int noutside)
{
  int n, i, j;

  newoutside[0] = u;
  newoutside[1] = v;
  n = 2;

  for (i = v_index; i != u_index; i = j) {
    j = (i+1) % noutside;
  
    /* add only if it's not duplicate */
    if (dist(outside[j], newoutside[n-1]) >= EPS &&
	dist(outside[j], newoutside[0]) >= EPS) {
      newoutside[n++] = outside[j];
    }
  }
  return n;
}

void do_it(Point *outside, int noutside, int *used, int edges, double cut) 
{ 
  Point newoutside[10*MAX_POLY];     /* just to be safe */
  int new_num;
  int i, u_index, v_index;
  Point u, v, a, b;

  if (edges == npoly) {
    if (cut < min_cut) {
/*
      for (i = 0; i < npoly; i++) {
        printf("%d: (%.4f,%.4f) --> (%.4f,%.4f)\n", cuts[i],
               cut_u[i].x, cut_u[i].y, cut_v[i].x, cut_v[i].y);
      }
*/
      min_cut = cut;
    }
    return;
  }

/*
  if (cut >= min_cut) {
    return;
  }
*/

/*
  for (i = 0; i < npoly; i++) {
    if (!used[i]) {
      a = poly[i];
      b = poly[(i+1) % npoly];
      if (coincident(a, b, outside, noutside)) {
	used[i] = 1;
	do_it(outside, noutside, used, edges+1, cut);
	used[i] = 0;
	return;
      }
    }
  }
*/

  for (i = 0; i < npoly; i++) {
    if (!used[i]) {
      used[i] = 1;
      a = poly[i];
      b = poly[(i+1) % npoly];
      u = find_lower(a, b, outside, noutside, &u_index);
      v = find_upper(a, b, outside, noutside, &v_index);
      cuts[edges] = i;
      cut_u[edges] = u;
      cut_v[edges] = v;
      new_num = get_outside(newoutside, u, v, u_index, v_index, 
			    outside, noutside);
      do_it(newoutside, new_num, used, edges+1, cut+dist(u,v));
      used[i] = 0;
    }
  }
}

void docase(void)
{
  Point outside[4];
  int used[MAX_POLY];
  int n, m, i;

  scanf("%d %d", &n, &m);
  outside[0].x = 0;  outside[0].y = 0;
  outside[1].x = 0;  outside[1].y = m;
  outside[2].x = n;  outside[2].y = m;
  outside[3].x = n;  outside[3].y = 0;

  scanf("%d", &npoly);

  for (i = 0; i < npoly; i++) {
    used[i] = 0;
    scanf("%lf %lf", &(poly[i].x), &(poly[i].y));
  }

  min_cut = 1e50;
  do_it(outside, 4, used, 0, 0);
  printf("Minimum total length = %.3f\n", min_cut);
  
}

int main(void)
{
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    docase();
    if (cases > 0) {
      printf("\n");
    }
  }
  return 0;
}
