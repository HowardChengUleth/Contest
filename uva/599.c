/* @JUDGE_ID: 1102NT 599 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char graph[26][26];
char vertex[26];

void clear_graph(void)
{
  int i, j;

  for (i = 0; i < 26; i++) {
    for (j = 0; j < 26; j++) {
      graph[i][j] = 0;
    }
    vertex[i] = 0;
  }
}

void read_graph(void)
{
  char buffer[1024];
  char u, v;
  int i;

  while (fgets(buffer, 1024, stdin) && buffer[0] != '*') {
    sscanf(buffer, "(%c,%c)", &u, &v);
    u -= 'A';
    v -= 'A';
    graph[u][v] = graph[v][u] = 1;
  }
  
  fgets(buffer, 1024, stdin);
  for (i = 0; buffer[i] != '\n'; i++) {
    if (isupper(buffer[i])) {
      vertex[buffer[i]-'A'] = 1;
    }
  }
}

int DFS(int parent, int v, char *visited)
{
  int w, cycle;

  visited[v] = 1;
  cycle = 0;
  for (w = 0; w < 26; w++) {
    if (!vertex[w] || !graph[v][w]) continue;
    if (w != parent && visited[w]) {
      cycle = 1;
    }
    if (!visited[w]) {
      cycle |= DFS(v, w, visited);
    }
  }
  return cycle;
}

int count_trees(void)
{
  int count;
  int i;
  char visited[26];
  
  count = 0;
  memset(visited, 0, 26);
  for (i = 0; i < 26; i++) {
    if (visited[i] || !vertex[i]) continue;
    if (!DFS(-1, i, visited)) {
      count++;
    }
  }
  return count;
}

int count_acorns(void)
{
  int count;
  int i, j;

  count = 0;
  for (i = 0; i < 26; i++) {
    if (!vertex[i]) continue;
    for (j = 0; j < 26; j++) {
      if (graph[i][j]) break;
    }
    if (j == 26) {
      count++;
    }
  }
  return count;
}

int main(void)
{
  int cases;
  int acorns, trees;

  scanf("%d\n", &cases);
  while (cases-- > 0) {
    clear_graph();
    read_graph();
    trees = count_trees();
    acorns = count_acorns();
    printf("There are %d tree(s) and %d acorn(s).\n", trees - acorns, acorns);
  }
  return 0;
}
