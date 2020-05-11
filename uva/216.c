/* @JUDGE_ID: 1102NT 216 C "" */

#include <stdio.h>
#include <math.h>

typedef struct {
  int x, y;
} Point;

int best_perm[8];
double best_len;

double dist(Point p1, Point p2)
{
  return 16 + sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

int read_case(Point *p)
{
  int n, i;
  scanf("%d", &n);

  for (i = 0; i < n; i++) {
    scanf("%d %d", &(p[i].x), &(p[i].y));
  }
  return n;
}

void permutations(Point *p, int *perm, int n, int start)
{
  int i, t;
  double len;
  if (start == n) {
    len = 0;
    for (i = 0; i < n-1; i++) {
      len += dist(p[perm[i]], p[perm[i+1]]);
    }
    if (best_len < 0 || len < best_len) {
      best_len = len;
      for (i = 0; i < n; i++) {
	best_perm[i] = perm[i];
      }
    }
  } else {
    for (i = start; i < n; i++) {
      t = perm[i];
      perm[i] = perm[start];
      perm[start] = t;
      permutations(p, perm, n, start+1);
      t = perm[i];
      perm[i] = perm[start];
      perm[start] = t;
    }
  }
}

int main(void)
{
  Point p[8];
  int n, i;
  int perm[8];
  int network = 0;

  while (n = read_case(p)) {
    for (i = 0; i < n; i++) {
      perm[i] = i;
    }
    best_len = -1;
    permutations(p, perm, n, 0);
    
    printf("**********************************************************\n");
    printf("Network #%d\n", ++network);
    for (i = 0; i < n-1; i++) {
      printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2f feet.\n",
	     p[best_perm[i]].x, p[best_perm[i]].y, 
	     p[best_perm[i+1]].x, p[best_perm[i+1]].y,
	     dist(p[best_perm[i]], p[best_perm[i+1]]));
    }
    printf("Number of feet of cable required is %.2f.\n", best_len);
  }
  return 0;
}
