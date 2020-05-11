/* @JUDGE_ID: 1102NT 459 C "" */

#include <stdio.h>

void DFS(char graph[26][26], int n, int v, int *visited, int label)
{
  int w;

  visited[v] = label;
  for (w = 0; w < n; w++) {
    if (graph[v][w] && visited[w] < 0) {
      DFS(graph, n, w, visited, label);
    }
  }
}

int main(void)
{
  char graph[26][26];
  char last;
  char buffer[1024];
  int n, i, j;
  int cases;
  int visited[26];
  int comp;

  fgets(buffer, 1024, stdin);
  sscanf(buffer, "%d", &cases);
  fgets(buffer, 1024, stdin);
  while (cases-- > 0) {
    fgets(buffer, 1024, stdin);
    sscanf(buffer, "%c", &last);

    n = last - 'A' + 1;
    
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	graph[i][j] = 0;
      }
    }

    while (fgets(buffer, 1024, stdin) && buffer[0] != '\n') {
      graph[buffer[0]-'A'][buffer[1]-'A'] = 1;
      graph[buffer[1]-'A'][buffer[0]-'A'] = 1;
    }

    for (i = 0; i < n; i++) {
      visited[i] = -1;
    }
    comp = 0;
    for (i = 0; i < n; i++) {
      if (visited[i] < 0) {
	DFS(graph, n, i, visited, comp++);
      }
    }
    printf("%d\n", comp);

    if (cases > 0) {
      printf("\n");
    }
  }
  return 0;
}
