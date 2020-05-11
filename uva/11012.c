#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
  int x, y, z;
} Point;

int n;
Point list[100000];

void read_case(void)
{
  int i;

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d %d %d", &list[i].x, &list[i].y, &list[i].z);
  }
}

void solve_case(void)
{
  int i;
  int best = INT_MIN;
  int best1, best2;
  int d;

  /* maximize (x[i]-x[j]) + (y[i]-y[j]) + (z[i]-z[j]) by finding
     a point i that maximizes x+y+z and j that maximizes -x-y-z.
     Also takes care of -(x[i]-x[j]) - (y[i]-y[j]) - (z[i]-z[j]) by 
     symmetry */
  best1 = INT_MIN;
  best2 = INT_MIN;
  for (i = 0; i < n; i++) {
    d = list[i].x + list[i].y + list[i].z;
    if (d > best1) best1 = d;
    if (-d > best2) best2 = -d;
  }
  if (best1 + best2 > best) {
    best = best1 + best2;
  }

  /* now maximize -x[i]+y[i]+z[i] and x[j]-y[j]-z[j] */
  best1 = INT_MIN;
  best2 = INT_MIN;
  for (i = 0; i < n; i++) {
    d = -list[i].x + list[i].y + list[i].z;
    if (d > best1) best1 = d;
    if (-d > best2) best2 = -d;
  }
  if (best1 + best2 > best) {
    best = best1 + best2;
  }

  /* now maximize x[i]-y[i]+z[i] and -x[j]+y[j]-z[j] */
  best1 = INT_MIN;
  best2 = INT_MIN;
  for (i = 0; i < n; i++) {
    d = list[i].x - list[i].y + list[i].z;
    if (d > best1) best1 = d;
    if (-d > best2) best2 = -d;
  }
  if (best1 + best2 > best) {
    best = best1 + best2;
  }

  /* now maximize x[i]+y[i]-z[i] and -x[j]-y[j]+z[j] */
  best1 = INT_MIN;
  best2 = INT_MIN;
  for (i = 0; i < n; i++) {
    d = list[i].x + list[i].y - list[i].z;
    if (d > best1) best1 = d;
    if (-d > best2) best2 = -d;
  }
  if (best1 + best2 > best) {
    best = best1 + best2;
  }
  
  

  printf("%d\n", best);
}

int main(void)
{
  int N, i;

  scanf("%d", &N);
  for (i = 1; i <= N; i++) {
    printf("Case #%d: ", i);
    read_case();
    solve_case();
  }
  return 0;
}
