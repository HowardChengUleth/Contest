/* @JUDGE_ID: 1102NT 10004 C "" */

#include <stdio.h>
#include <string.h>

char adj[200][200];
int n;

int dfs(int v, char *visited, int *color, int c)
{
  int w;

  visited[v] = 1;
  color[v] = c;

  for (w = 0; w < n; w++) {
    if (adj[v][w]) {
      if (!visited[w]) {
	if (!dfs(w, visited, color, 1-c)) {
	  return 0;
	}
      } else if (color[w] == c) {
	return 0;
      }
    }
  }

  return 1;
}

int main(void)
{
  char visited[200];
  int color[200];
  int i, j, l;

  while (scanf("%d", &n) == 1 && n > 0) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	adj[i][j] = 0;
      }
    }

    scanf("%d", &l);
    while (l-- > 0) {
      scanf("%d %d", &i, &j);
      adj[i][j] = adj[j][i] = 1;
    }

    for (i = 0; i < n; i++) {
      color[i] = -1;
    }
    memset(visited, 0, n);
    if (dfs(0, visited, color, 0)) {
      printf("BICOLORABLE.\n");
    } else {
      printf("NOT BICOLORABLE.\n");
    }
  }

  return 0;
}
