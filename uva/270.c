/* @JUDGE_ID: 1102NT 270 C "" */

/* modified to make I/O work with the Spain judge */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

typedef struct {
  int x, y;
  double ang;
} Point;

Point point[700];
int best;
int n;

int cmp(const void *a, const void *b)
{
  Point *p = (Point *)a;
  Point *q = (Point *)b;
  double t = p->ang - q->ang;

  if (t > 0) {
    return 1;
  } else if (t < 0) {
    return -1;
  } else {
    return 0;
  }
}

int main(void) 
{
  int i, j, c;
  double t, pi;
  char buffer[10240];

  pi = atan(1)*4;
  while (scanf("%d", &n) == 1 && n > 0) {
    best = 1;
    for (i = 0; i < n; i++) {
      scanf("%d %d", &(point[i].x), &(point[i].y));
    }
  
    for (i = 0; i < n - best; i++) {
      for (j = i+1; j < n; j++) {
	t = atan2(point[j].y-point[i].y, point[j].x-point[i].x);
	while (t < 0.0) {
	  t += pi;
	}
	point[j].ang = t;
      }
      qsort(&(point[i+1]), n-i-1, sizeof(Point), cmp);
      c = 1;
      for (j = i+2; j < n; j++) {
	if (fabs(point[j].ang - point[j-1].ang) < 1E-8) {
	  c++;
	} else {
	  if (c > best) {
	    best = c;
	  }
	  c = 1;
	}
      }
      if (c > best) {
	best = c;
      }
    }
    printf("%d\n", best+1);
  }
  return 0;
}
