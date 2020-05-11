#include <stdio.h>

int G[25][25];
int n, m;

int read_case(void)
{
  int i;
  int u, v;

  scanf("%d %d", &n, &m);
  if (!n && !m) return 0;

  for (u = 0; u < n; u++) {
    for (v = 0; v < n; v++) {
      G[u][v] = 0;
    }
  }

  for (i = 0; i < m; i++) {
    scanf("%d %d", &u, &v);
    G[u][v] = G[v][u] = 1;
  }

  return 1;
}

int length_from(int v)
{
  int w;
  int best = 0;
  int t;

  
  for (w = 0; w < n; w++) {
    if (G[v][w]) {
      G[v][w] = G[w][v] = 0;
      t = 1 + length_from(w);
      G[v][w] = G[w][v] = 1;
      if (t > best) {
	best = t;
      }
    }
  }

  return best;
}

void solve_case(void)
{
  int v;
  int best = -1;
  int t;

  /* try all starting points */
  for (v = 0; v < n; v++) {
    t = length_from(v);
    if (t > best) {
      best = t;
    }
  }

  printf("%d\n", best);
}


int main(void)
{
  while (read_case()) {
    solve_case();
  }
  return 0;
}
