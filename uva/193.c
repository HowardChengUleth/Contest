/* @JUDGE_ID: 1102NT 193 C "" */

#include <stdio.h>
#include <string.h>

int read_graph(char graph[100][100])
{
  int n, m, i, j;

  scanf("%d %d", &n, &m);
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      graph[i][j] = 0;
    }
  }
  while (m-- > 0) {
    scanf("%d %d", &i, &j);
    graph[i-1][j-1] = graph[j-1][i-1] = 1;
  }
  return n;
}

int best;
char best_black[100];

void solve(char graph[100][100], int n, int index, char *black, int sofar, 
	   char *bad)
{
  int list[100], list_num = 0;
  int i;

  if (n == index) {
    if (sofar > best) {
      best = sofar;
      for (i = 0; i < n; i++) {
	best_black[i] = black[i];
      }
    }
    return;
  }

  if (sofar + n - index <= best) {
    return;
  }

  if (!bad[index]) {
    for (i = index+1; i < n; i++) {
      if (graph[index][i] && !bad[i]) {
	bad[i] = 1;
	list[list_num++] = i;
      }
    }
    black[index] = 1;
    solve(graph, n, index+1, black, sofar+1, bad);
    black[index] = 0;
    for (i = 0; i < list_num; i++) {
      bad[list[i]] = 0;
    }
  }

  solve(graph, n, index+1, black, sofar, bad);

}

int main(void)
{
  int m, n, i;
  char black[100], graph[100][100], bad[100];
  char first;

  scanf("%d", &m);
  while (m-- > 0) {
    n = read_graph(graph);
    memset(black, 0, n);
    memset(bad, 0, n);
    best = 0;
    solve(graph, n, 0, black, 0, bad);
    printf("%d\n", best);
    first = 1;
    for (i = 0; i < n; i++) {
      if (best_black[i]) {
	if (!first) {
	  printf(" ");
	}
	printf("%d", i+1);
	first = 0;
      }
    }
    printf("\n");
  }
  return 0;
}
