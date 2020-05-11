#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 22
#define MAX_NAME 10

int N, M;
char names[MAX_N][MAX_NAME+1];
int graph[MAX_N][MAX_N];

void clear_graph(void)
{
  int i, j;

  for (i = 0; i < MAX_N; i++) {
    for (j = 0; j < MAX_N; j++) {
      graph[i][j] = MAX_N*10000;
    }
    graph[i][i] = 0;
  }
}

int read_case(void)
{
  int t, i, j, k;

  scanf("%d %d", &N, &M);
  if (!N) {
    return 0;
  }

  clear_graph();
  for (i = 0; i < N; i++) {
    scanf("%s", names[i]);
  }

  for (t = 0; t < M; t++) {
    scanf("%d %d %d", &i, &j, &k);
    i--;
    j--;
    graph[i][j] = graph[j][i] = k;
  }

  return 1;
}

int cost(int dest)
{
  int sum = 0;
  int i;

  for (i = 0; i < N; i++) {
    sum += graph[i][dest];
  }
  
  return sum;
}

void solve_case(int case_num)
{
  int i, j, k;
  int best, best_i;

  for (k = 0; k < N; k++) {
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
	if (graph[i][j] > graph[i][k] + graph[k][j]) {
	  graph[i][j] = graph[i][k] + graph[k][j];
	}
      }
    }
  }

  best = cost(0);
  best_i = 0;
  for (i = 1; i < N; i++) {
    if ((k = cost(i)) < best) {
      best = k;
      best_i = i;
    }
  }

  printf("Case #%d : %s\n", case_num, names[best_i]);
}

int main(void)
{
  int cases = 0;
  while (read_case()) {
    solve_case(++cases);
  }

  return 0;
}
