/* @JUDGE_ID: 1102NT 754 C "" */

/* Copyright Howard Cheng (ACM ICPC ECNA 1999) */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define MAX_WALLS (30+4)
#define MAX_SIZE 100
#define MAX_NODES (MAX_WALLS*(MAX_WALLS-1)+2)
#define EPS 1e-8

typedef struct {
  double x, y;
} Point;

typedef struct {
  Point p1, p2;
} Line;

typedef struct {
  Point p;               /* point that defines the node */
  int wall;
  int deg;
  int adj[MAX_NODES];
} Node;

typedef struct {
  double r;
  Point p;
} Intersection;

int n_walls;
int n_nodes;
Line wall[MAX_WALLS];
Point treasure;
Node graph[MAX_NODES];

int icmp(const void *a, const void *b)
{
  Intersection *x = (Intersection *)a;
  Intersection *y = (Intersection *)b;
  double x1 = x->r;
  double y1 = y->r;

  if (fabs(x1 - y1) < EPS) {
    return 0;
  } else if (x1 < y1) {
    return -1;
  } else {
    return 1;
  }
}

double dist_line(Point a, Point b, Point c)
{
  double L2, s;

  L2 = (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
  assert(L2 > 0);
  s = ((a.y-c.y)*(b.x-a.x)-(a.x-c.x)*(b.y-a.y)) / L2;

  return fabs(s*sqrt(L2));
}

/* returns 1 if intersect at a point, 0 otherwise */
int intersect(Line l1, Line l2, Point *p, double *r)
{
  double s;
  double denom, num1, num2;
  Point a = l1.p1, b = l1.p2, c = l2.p1, d = l2.p2;

  assert((a.x != b.x || a.y != b.y) && (c.x != d.x || c.y != d.y));

  num1 = (a.y - c.y)*(d.x - c.x) - (a.x - c.x)*(d.y - c.y);
  num2 = (a.y - c.y)*(b.x - a.x) - (a.x - c.x)*(b.y - a.y);
  denom = (b.x - a.x)*(d.y - c.y) - (b.y - a.y)*(d.x - c.x);

  if (fabs(denom) >= EPS) {
    *r = num1 / denom;
    s = num2 / denom;
    if (0-EPS <= *r && *r <= 1+EPS && 0-EPS <= s && s <= 1+EPS) {
      p->x = a.x + (*r)*(b.x - a.x);
      p->y = a.y + (*r)*(b.y - a.y);
      return 1;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

void read_case(void)
{
  int i, t;

  t = scanf("%d", &n_walls);
  assert(t == 1 && 0 <= n_walls && n_walls+4 <= MAX_WALLS);
  for (i = 0; i < n_walls; i++) {
    t = scanf("%lf %lf %lf %lf", &(wall[i].p1.x), &(wall[i].p1.y),
	      &(wall[i].p2.x), &(wall[i].p2.y));
    assert(t == 4);
    assert(0 <= wall[i].p1.x && wall[i].p1.x <= MAX_SIZE);
    assert(0 <= wall[i].p1.y && wall[i].p1.y <= MAX_SIZE);
    assert(0 <= wall[i].p2.x && wall[i].p2.x <= MAX_SIZE);
    assert(0 <= wall[i].p2.y && wall[i].p2.y <= MAX_SIZE);
  }
  t = scanf("%lf %lf", &(treasure.x), &(treasure.y));
  assert(t == 2 && 0 <= treasure.x && treasure.x <= MAX_SIZE &&
	 0 <= treasure.y && treasure.y <= MAX_SIZE);

  /* add the four outside walls */
  wall[n_walls].p1.x = wall[n_walls].p1.y = 0;
  wall[n_walls].p2.x = 0; wall[n_walls++].p2.y = MAX_SIZE;

  wall[n_walls].p1.x = wall[n_walls].p1.y = 0;
  wall[n_walls].p2.x = MAX_SIZE; wall[n_walls++].p2.y = 0;

  wall[n_walls].p1.x = wall[n_walls].p1.y = MAX_SIZE;
  wall[n_walls].p2.x = 0; wall[n_walls++].p2.y = MAX_SIZE;

  wall[n_walls].p1.x = wall[n_walls].p1.y = MAX_SIZE;
  wall[n_walls].p2.x = MAX_SIZE; wall[n_walls++].p2.y = 0;

  for (i = 0; i < n_walls; i++) {
    assert(dist_line(wall[i].p1, wall[i].p2, treasure) >= 0.5);
  }
}

void compute_points(void)
{
  int i, j, n_inter;
  Intersection inter[MAX_WALLS-1];
  double prev;
  Point prev_p;
  
  /* add tresure point */
  graph[1].wall = -1;
  graph[1].p = treasure;

  n_nodes = 2;
  for (i = 0; i < n_walls; i++) {
    n_inter = 0;
    for (j = 0; j < n_walls; j++) {
      if (i != j) {
	if (intersect(wall[i], wall[j], &(inter[n_inter].p), 
		      &(inter[n_inter].r))) {
	  n_inter++;
	}
      }
    }

    qsort(inter, n_inter, sizeof(Intersection), icmp);
    
    prev = 0.0;
    for (j = 0; j < n_inter; j++) {
      if (fabs(prev - inter[j].r) > EPS) {
	graph[n_nodes].wall = i;
	graph[n_nodes].p.x = (prev_p.x + inter[j].p.x) / 2.0;
	graph[n_nodes].p.y = (prev_p.y + inter[j].p.y) / 2.0;
	n_nodes++;
      } else {
	assert(j == 0);
      }
      prev = inter[j].r;
      prev_p = inter[j].p;
    }
  }
}

void add_edge(int v, int w)
{
  assert(graph[v].deg < MAX_NODES && graph[w].deg < MAX_NODES);
  graph[v].adj[graph[v].deg++] = w;
  graph[w].adj[graph[w].deg++] = v;
}

void build_graph(void)
{
  /* node 0 = outside */
  /* node 1 = treasure */
  /* 2 to n_nodes-1 = midpoints of walls */

  Line line;
  Point p;
  double r;
  int i, j, k, visible;

  /* clear graph */
  for (i = 0; i < n_nodes; i++) {
    graph[i].deg = 0;
  }

  for (i = 2; i < n_nodes; i++) {
    /* check for external walls */
    p = graph[i].p;
    if (fabs(p.x) < EPS || fabs(p.y) < EPS || fabs(p.x - MAX_SIZE) < EPS ||
	fabs(p.y - MAX_SIZE) < EPS) {
      add_edge(0, i);
    }
  }

  /* check other walls and treasure point */
  for (i = 1; i < n_nodes; i++) { 
    line.p1 = graph[i].p;
    for (j = i+1; j < n_nodes; j++) {
      line.p2 = graph[j].p;
      visible = 1;
      for (k = 0; k < n_walls && visible; k++) {
	if (k != graph[i].wall && k != graph[j].wall && 
	    intersect(line, wall[k], &p, &r)) {
	  visible = 0;
	}
      }
      if (visible) {
	add_edge(i, j);
      }
    }
  }
}

void print_graph(void)
{
  int i, j;

  printf("Graph:\n\n");
  for (i = 0; i < n_nodes; i++) {
    printf("%2d:", i);
    for (j = 0; j < graph[i].deg; j++) {
      printf(" %2d", graph[i].adj[j]);
    }
    printf("\n");
  }
}

void BFS_path(Node graph[MAX_NODES], int n, int src, int D[MAX_NODES])
{
  char used[MAX_NODES];
  int queue[MAX_NODES+1];
  int q_in, q_out, i;
  int v, w;

  memset(used, 0, MAX_NODES);
  queue[0] = src;
  used[src] = 1;
  q_in = 1;
  q_out = 0;
  
  for (i = 0; i < MAX_NODES; i++) {
    D[i] = -1;
  }
  D[src] = 0;

  while (q_out < q_in) {
    v = queue[q_out++];
    for (i = 0; i < graph[v].deg; i++) {
      w = graph[v].adj[i];
      if (!used[w]) {
        D[w] = D[v] + 1;
        queue[q_in++] = w;
        used[w] = 1;
      }
    }
  }
}

void solve_case(void)
{
  int D[MAX_NODES];

  read_case();
  compute_points();
  build_graph();
/*
  print_graph();
*/
  BFS_path(graph, n_nodes, 0, D);

  printf("Number of doors = %d\n", D[1] - 1);
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
