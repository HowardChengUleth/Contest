/* @JUDGE_ID: 1102NT 315 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_graph(char graph[101][101])
{
  char buffer[1000], *p;
  int n, i, j;

  for (i = 0; i <= 100; i++) {
    for (j = 0; j <= 100; j++) {
      graph[i][j] = 0;
    }
  }
  
  scanf("%d", &n);
  if (n == 0) {
    return 0;
  }

  scanf("\n");
  while (fgets(buffer, 1000, stdin) && atoi(buffer) != 0) {
    p = strtok(buffer, " \n");
    i = atoi(p);
    while (p = strtok(0, " \n")) {
      j = atoi(p);
      graph[i][j] = graph[j][i] = 1;
    }
  }
  
  return n;
}

void dfs(int n, char graph[101][101], int v, char *visited)
{
  int w;

  visited[v] = 1;
  for (w = 1; w <= n; w++) {
    if (graph[v][w] && !visited[w]) {
      dfs(n, graph, w, visited);
    }
  }
}

int connected(int n, char graph[101][101], int k)
{
  char visited[101];
  int i;

  if (n == 1) {
    return 1;
  }

  memset(visited, 0, 101);
  dfs(n, graph, (k == 1) ? 2 : 1, visited);
  for (i = 1; i <= n; i++) {
    if (i != k && !visited[i]) {
      return 0;
    }
  }
  return 1;
}

void solve_case(int n, char graph[101][101])
{
  char graph2[101][101];
  int i, j, k;
  int count = 0;

  for (k = 1; k <= n; k++) {
    for (i = 0; i <= n; i++) {
      for (j = 0; j <= n; j++) {
	graph2[i][j] = graph[i][j];
      }
    }
    for (i = 0; i <= n; i++) {
      graph2[i][k] = graph2[k][i] = 0;
    }
    if (!connected(n, graph2, k)) {
      count++;
    }
  }

  printf("%d\n", count);
}

int main(void)
{
  char graph[101][101];
  int n;

  while (n = read_graph(graph)) {
    solve_case(n, graph);
  }
  return 0;
}
