#include <stdio.h>

int G[101][101];
int n, s;

int read_graph(void)
{
  int i, j, p, q;

  scanf("%d", &n);
  if (!n) {
    return 0;
  }
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      G[i][j] = 0;
    }
  }

  scanf("%d", &s);
  while (scanf("%d %d", &p, &q) == 2 && (p || q)) {
    G[p][q] = 1;
  }
  return 1;
}

int len[101], fin[101];

int DFS(int v, int *finish)
{
  int w;
  int d = 0;
  int f, t;

  if (len[v] >= 0) {
    *finish = fin[v];
    return len[v];
  }

  *finish = v;

  for (w = 1; w <= n; w++) {
    if (!G[v][w]) continue;
    t = DFS(w, &f) + 1;
    if (t > d || (t == d && f < *finish)) {
      d = t;
      *finish = f;
    }
  }
  fin[v] = *finish;
  return len[v] = d;
}

int main(void)
{
  int case_no = 1;
  int length, finish;
  int i;

  while (read_graph()) {
    for (i = 1; i <= n; i++) {
      len[i] = -1;
      fin[i] = -1;
    }
      
    length = DFS(s, &finish);
    printf("Case %d: The longest path from %d has length %d, finishing"
	   " at %d.\n\n", case_no++, s, length, finish);
  }
  return 0;
}
