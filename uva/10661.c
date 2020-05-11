/* @JUDGE_ID: 1102NT 10661 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_M 19

char graph[MAX_M][MAX_M];
int M;

void clear_graph(void)
{
  int i, j;
  for (i = 0; i < MAX_M; i++) {
    for (j = 0; j < MAX_M; j++) {
      graph[i][j] = 0;
    }
  }
}

void read_graph(void)
{
  int P;
  char v1[2], v2[2];

  clear_graph();
  scanf("%d %d", &M, &P);
  while (P-- > 0) {
    scanf("%s %s", v1, v2);
    graph[v1[0]-'A'][v2[0]-'A'] = 1;
    graph[v2[0]-'A'][v1[0]-'A'] = 1;
  }
}

signed char clique[(1 << MAX_M)];

int search_clique(int mask, int size)
{
  int ans = 0;
  int i, j, t;

  if (mask == 0) {
    clique[mask] = 1;
    return 0;
  } else if (clique[mask] > 0) {
    return size;
  } else if (clique[mask] == 0) {
    return ans;
  }

  for (i = 0; i < M; i++) {
    if (mask & (1 << i)) {
      t = search_clique(mask - (1 << i), size-1);
      if (t > ans) {
	ans = t;
      }
      if (!clique[mask - (1 << i)]) continue;
      for (j = 0; j < M; j++) {
	if (i != j && (mask & (1 << j)) && !graph[i][j]) {
	  break;
	}
      }
      if (j == M) {
	clique[mask] = 1;
	return size;
      }
    }
  }
  clique[mask] = 0;
  return ans;
}

int try_color(int *color, int index, int max_colors)
{
  int c, j;

  if (index == M) {
    return 1;
  }

  for (c = 0; c < max_colors; c++) {
    for (j = 0; j < index; j++) {
      if (graph[index][j] && color[j] == c) {
	break;
      }
    }
    if (j < index) continue;
    color[index] = c;
    if (try_color(color, index+1, max_colors)) {
      return 1;
    }
  }
  return 0;
}

int mincolor(void)
{
  int clique_size;
  int color[MAX_M];
  int max_colors;

  memset(clique, -1, 1 << M);
  clique_size = search_clique((1 << M) - 1, M);

  for (max_colors = clique_size; max_colors <= M; max_colors++) {
    color[0] = 0;
    if (try_color(color, 1, max_colors)) {
      return max_colors;
    }
  }

  assert(0);
}

int main(void)
{
  int N;

  scanf("%d", &N);
  while (N-- > 0) {
    read_graph();
    printf("%d\n", mincolor());
  }
  return 0;
}
