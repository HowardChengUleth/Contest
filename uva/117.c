#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define MAX_NODES  26
#define DISCONNECT -1

int graph[MAX_NODES][MAX_NODES];

void clear_graph(void)
{
  int i, j;
  for (i = 0; i < MAX_NODES; i++) {
    for (j = 0; j < MAX_NODES; j++) {
      graph[i][j] = DISCONNECT;
    }
  }
}

int read_graph(void)
{
  char buffer[1024];
  int sum = 0;

  if (scanf("%s", buffer) != 1) {
    return 0;
  }

  while (strcmp(buffer, "deadend")) {
    int len = strlen(buffer);
    int n1 = buffer[0] - 'a';
    int n2 = buffer[len-1] - 'a';
    graph[n1][n2] = graph[n2][n1] = len;
    sum += len;
    scanf("%s", buffer);
  }

  return sum;
}

int find_odd(int *n1, int *n2)
{
  int i, j;
  int count = 0;
  int deg;
  for (i = 0; i < MAX_NODES; i++) {
    deg = 0;
    for (j = 0; j < MAX_NODES; j++) {
      if (graph[i][j] != DISCONNECT) {
        deg++;
      }
    }
    if (deg % 2 == 1) {
      if (count == 0) {
        *n1 = i;
      } else if (count == 1) {
        *n2 = i;
      } else {
        assert(0);
      }
      count++;
    }
  }
  return count;
}

void floyd(void)
{
  int i, j, k;

  for (k = 0; k < MAX_NODES; k++) {
    for (i = 0; i < MAX_NODES; i++) {
      for (j = 0; j < MAX_NODES; j++) {
        if (graph[i][k] != DISCONNECT && graph[k][j] != DISCONNECT) {
          int temp = graph[i][k] + graph[k][j];
          if (graph[i][j] == DISCONNECT) {
            graph[i][j] = temp;
          } else if (graph[i][j] > temp) {
            graph[i][j] = temp;
          }
        }
      }
    }
  }
}

int main(void)
{
  int sum;
  int n1, n2;
  int t;
  
  clear_graph();
  while ((sum = read_graph()) > 0) {
    if ((t = find_odd(&n1, &n2)) == 2) {
      floyd();
      printf("%d\n", sum+graph[n1][n2]);
    } else {
      assert(t == 0);
      printf("%d\n", sum);
    }
    clear_graph();
  }

  return 0;
}

