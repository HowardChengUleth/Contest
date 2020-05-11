/* @JUDGE_ID: 1102NT 10457 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int deg;
  int nbr[1000];
  int speed[1000];
} Node;

Node graph[200];
int speeds[1000];
int N, num_speeds;

int cmp(const void *a, const void *b)
{
  return *(int *)a - *(int *)b;
}

int read_graph(void)
{
  int i, M, u, v, s;

  if (scanf("%d %d", &N, &M) != 2) {
    return 0;
  }

  for (i = 0; i < N; i++) {
    graph[i].deg = 0;
  }
  
  for (i = 0; i < M; i++) {
    scanf("%d %d %d", &u, &v, &s);
    u--; v--;
    graph[u].nbr[graph[u].deg] = v;
    graph[u].speed[graph[u].deg++] = s;
    graph[v].nbr[graph[v].deg] = u;
    graph[v].speed[graph[v].deg++] = s;
    speeds[i] = s;
  }

  qsort(speeds, M, sizeof(*speeds), cmp);
  num_speeds = 0;
  for (i = 0; i < M; i++) {
    if (!i || speeds[i-1] != speeds[i]) {
      speeds[num_speeds++] = speeds[i];
    }
  }

  return 1;
}

int reachable(int src, int dest, int l, int u, char *visited)
{
  int i;

  visited[src] = 1;
  if (src == dest) {
    return 1;
  }

  for (i = 0; i < graph[src].deg; i++) {
    if (l <= graph[src].speed[i] && graph[src].speed[i] <= u &&
	!visited[graph[src].nbr[i]]) {
      if (reachable(graph[src].nbr[i], dest, l, u, visited)) {
	return 1;
      }
    }
  }
  return 0;
}

int best_window(int src, int dest, int lower, int best_so_far)
{
  int lo, hi, mid;
  int *s = speeds + lower;
  char visited[200];

  /* let's try to find the largest index "hi" for s such that
   * s[hi] - s[0] < best_so_far (which is positive)
   */
  lo = 0;
  hi = num_speeds - 1 - lower;
  if (s[hi] - s[0] >= best_so_far) {
    while (hi - lo > 1) {
      mid = (lo + hi) / 2;
      if (s[mid] - s[0] < best_so_far) {
	lo = mid;
      } else {
	hi = mid;
      }
    }
    hi = lo;
  }

  lo = 0;

  /*
   * invariant:
   *
   * we cannot do a window of size "lo", but we can do a window of size "hi"
   *
   */

  /* establish invariant initially */
  memset(visited, 0, N);
  if (reachable(src, dest, s[0], s[lo], visited)) {
    return s[lo] - s[0];
  }
  memset(visited, 0, N);
  if (!reachable(src, dest, s[0], s[hi], visited)) {
    /* always worse */
    return best_so_far + 1;
  }

  /* now do binary search */
  while (hi - lo > 1) {
    mid = (lo + hi) / 2;
    memset(visited, 0, N);
    if (reachable(src, dest, s[0], s[mid], visited)) {
      hi = mid;
    } else {
      lo = mid;
    }
  }
  return s[hi] - s[0];
}

int solve(int src, int dest)
{
  int best = speeds[num_speeds-1] - speeds[0], i, t;

  for (i = 0; i < num_speeds; i++) {
    t = best_window(src, dest, i, best);
    if (t < best) {
      best = t;
    }
    if (!best) {
      return best;
    }
  }
  return best;
}

int main(void)
{
  int start, stop, K, src, dest;

  while (read_graph()) {
    scanf("%d %d", &start, &stop);
    scanf("%d", &K);
    while (K-- > 0) {
      scanf("%d %d", &src, &dest);
      printf("%d\n", solve(src-1, dest-1) + start + stop);
    }
  }

  return 0;
}
