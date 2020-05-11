/* @JUDGE_ID: 1102NT 273 C "" */

/* modified I/O to make online judge happy */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct {
  int x, y;
} Point;

typedef struct {
  Point p, q;
} Line;

Line line[20];
int graph[20][20];

int n;

int direction(Point p1, Point p2, Point p3)
{
  int x1 = p3.x - p1.x;
  int y1 = p3.y - p1.y;
  int x2 = p2.x - p1.x;
  int y2 = p2.y - p1.y;
  return x1*y2 - x2*y1;
}

int on_segment(Point p1, Point p2, Point p3)
{
  return ((p1.x <= p3.x && p3.x <= p2.x) || (p2.x <= p3.x && p3.x <= p1.x)) &&
    ((p1.y <= p3.y && p3.y <= p2.y) || (p2.y <= p3.y && p3.y <= p1.y));
}

int intersect(Point a1, Point a2, Point b1, Point b2)
{
  int d1 = direction(b1, b2, a1);
  int d2 = direction(b1, b2, a2);
  int d3 = direction(a1, a2, b1);
  int d4 = direction(a1, a2, b2);

  if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
      ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
    return 1;
  } else {
    return (d1 == 0 && on_segment(b1, b2, a1)) ||
      (d2 == 0 && on_segment(b1, b2, a2)) ||
      (d3 == 0 && on_segment(a1, a2, b1)) ||
      (d4 == 0 && on_segment(a1, a2, b2));
  }
}

void trans_closure(void)
{
  int i, j, k;

  for (k = 0; k < n; k++) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	graph[i][j] |= (graph[i][k] && graph[k][j]);
      }
    }
  }
}

int main(void)
{
  int i, j, u, v;
  int cases;

  scanf("%d", &cases);

  while (cases-- > 0) {
    scanf("%d", &n);
    if (n == 0) {
      printf("%d\n", cases);
      return 0;
    }
    for (i = 0; i < n; i++) {
      scanf("%d %d", &(line[i].p.x), &(line[i].p.y));
      scanf("%d %d", &(line[i].q.x), &(line[i].q.y));
    }
    
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	graph[i][j] = 0;
      }
    }
    for (i = 0; i < n; i++) {
      graph[i][i] = 1;
      for (j = i+1; j < n; j++) {
	if (intersect(line[i].p, line[i].q, line[j].p, line[j].q)) {
	  graph[i][j] = graph[j][i] = 1;
	}
      }
    }
    trans_closure();
    
    while (scanf("%d %d", &u, &v) == 2 && (u || v)) {
      if (!graph[u-1][v-1]) {
	printf("NOT ");
      }
      printf("CONNECTED\n");
    }
    if (cases) {
      printf("\n");
    }
  }
  return 0;
}

