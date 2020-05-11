/* @JUDGE_ID: 1102NT 754 C "" */

/* Copyright Howard Cheng (ACM ICPC ECNA 1999) */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define MAX_WALLS (30+4)
#define MAX_SIZE 100
#define EPS 1e-8

typedef struct {
  double x, y;
} Point;

typedef struct {
  Point p1, p2;
} Line;

int n_walls;
int n1, n2, n3, n4;
Line wall[MAX_WALLS];
int wall1[MAX_WALLS], wall2[MAX_WALLS], wall3[MAX_WALLS], wall4[MAX_WALLS];
Point treasure;

/* returns 1 if intersect at a point, 0 otherwise */
int intersect(Line l1, Line l2)
{
  double r, s;
  double denom, num1, num2;
  Point a = l1.p1, b = l1.p2, c = l2.p1, d = l2.p2;

  assert((a.x != b.x || a.y != b.y) && (c.x != d.x || c.y != d.y));

  num1 = (a.y - c.y)*(d.x - c.x) - (a.x - c.x)*(d.y - c.y);
  num2 = (a.y - c.y)*(b.x - a.x) - (a.x - c.x)*(b.y - a.y);
  denom = (b.x - a.x)*(d.y - c.y) - (b.y - a.y)*(d.x - c.x);

  if (fabs(denom) >= EPS) {
    r = num1 / denom;
    s = num2 / denom;
    return (0-EPS <= r && r <= 1+EPS && 0-EPS <= s && s <= 1+EPS);
  } else {
    return 0;
  }
}

int cmp(const void *a, const void *b)
{
  int x = *(int *)a;
  int y = *(int *)b;

  return x - y;
}

void read_case(void)
{
  int i, t;
  int a, b, c, d;
  
  t = scanf("%d", &n_walls);
  assert(t == 1 && 0 <= n_walls && n_walls+4 <= MAX_WALLS);
  n1 = n2 = n3 = n4 = 0;
  for (i = 0; i < n_walls; i++) {
    t = scanf("%d %d %d %d", &a, &b, &c, &d);
    wall[i].p1.x = a;
    wall[i].p1.y = b;
    wall[i].p2.x = c;
    wall[i].p2.y = d;
    if (a == 0) {
      wall1[n1++] = b;
    } else if (a == MAX_SIZE) {
      wall2[n2++] = b;
    }
    if (c == 0) {
      wall1[n1++] = d;
    } else if (c == MAX_SIZE) {
      wall2[n2++] = d;
    }
    if (b == 0) {
      wall3[n3++] = a;
    } else if (b == MAX_SIZE) {
      wall4[n4++] = a;
    }
    if (d == 0) {
      wall3[n3++] = c;
    } else if (d == MAX_SIZE) {
      wall4[n4++] = c;
    }
  }

  wall1[n1++] = MAX_SIZE;
  wall2[n2++] = MAX_SIZE;
  wall3[n3++] = MAX_SIZE;
  wall4[n4++] = MAX_SIZE;

  t = scanf("%lf %lf", &(treasure.x), &(treasure.y));
  assert(t == 2 && 0 <= treasure.x && treasure.x <= MAX_SIZE &&
	 0 <= treasure.y && treasure.y <= MAX_SIZE);

  qsort(wall1, n1, sizeof(int), cmp);
  qsort(wall2, n2, sizeof(int), cmp);
  qsort(wall3, n3, sizeof(int), cmp);
  qsort(wall4, n4, sizeof(int), cmp);
  assert(wall1[0] && wall2[0] && wall3[0] && wall4[0]);
}

void solve_case(void)
{
  int i, j, k, c;
  int mindoors = MAX_WALLS*100;
  double prev;
  Line L2;
  
  read_case();
  L2.p1 = treasure;
  
  prev = 0;
  L2.p2.x = 0;
  for (i = 0; i < n1; i++) {
    L2.p2.y = (prev + wall1[i]) / 2.0;
    c = 0;
    for (j = 0; j < n_walls && c < mindoors; j++) {
      c += intersect(wall[j], L2);
    }
    if (c < mindoors) {
      mindoors = c;
    }
    prev = wall1[i];
  }

  prev = 0;
  L2.p2.x = MAX_SIZE;
  for (i = 0; i < n2; i++) {
    L2.p2.y = (prev + wall2[i]) / 2.0;
    c = 0;
    for (j = 0; j < n_walls && c < mindoors; j++) {
      c += intersect(wall[j], L2);
    }
    if (c < mindoors) {
      mindoors = c;
    }
    prev = wall2[i];
  }

  prev = 0;
  L2.p2.y = 0;
  for (i = 0; i < n3; i++) {
    L2.p2.x = (prev + wall3[i]) / 2.0;
    c = 0;
    for (j = 0; j < n_walls && c < mindoors; j++) {
      c += intersect(wall[j], L2);
    }
    if (c < mindoors) {
      mindoors = c;
    }
    prev = wall3[i];
  }

  prev = 0;
  L2.p2.y = MAX_SIZE;
  for (i = 0; i < n4; i++) {
    L2.p2.x = (prev + wall4[i]) / 2.0;
    c = 0;
    for (j = 0; j < n_walls && c < mindoors; j++) {
      c += intersect(wall[j], L2);
    }
    if (c < mindoors) {
      mindoors = c;
    }
    prev = wall4[i];
  }

  printf("Number of doors = %d\n", mindoors+1);
}

int main(void)
{
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    solve_case();
    if (cases > 0) {
      printf("\n");
    }
  }
  return 0;
}
