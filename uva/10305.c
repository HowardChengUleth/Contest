#include <stdio.h>

int m, n;

int graph[101][101];

int read_case(void)
{
  int i, j, k;

  scanf("%d %d", &n, &m);
  if (!m && !n) return 0;

  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      graph[i][j] = 0;
    }
  }

  for (k = 0; k < m; k++) {
    scanf("%d %d", &i, &j);
    graph[j][i] = 1;
  }
  return 1;
}

int printed;

void process(int v, char *visited)
{
  int w;

  visited[v] = 1;
  for (w = 1; w <= n; w++) {
    if (graph[v][w] && !visited[w]) {
      process(w, visited);
    }
  }
  
  if (printed) {
    putchar(' ');
  }
  printf("%d", v);
  printed = 1;
}

void solve_case(void)
{
  char visited[101];
  int v;

  for (v = 1; v <= n; v++) {
    visited[v] = 0;
  }
  printed = 0;

  for (v = 1; v <= n; v++) {
    if (!visited[v]) {
      process(v, visited);
    }
  }
  
  printf("\n");

}

int main(void)
{
  while (read_case()) {
    solve_case();
  }
  return 0;
}
