/* @JUDGE_ID: 1102NT 10054 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_VERTICES 50

int graph[NUM_VERTICES+1][NUM_VERTICES+1];
int deg[NUM_VERTICES+1];

void clear_graph(void)
{
  int i, j;
  for (i = 1; i <= NUM_VERTICES; i++) {
    for (j = 1; j <= NUM_VERTICES; j++) {
      graph[i][j] = 0;
    }
    deg[i] = 0;
  }
}

void visit(int v, char *visited)
{
  int w;
  
  visited[v] = 1;
  for (w = 1; w <= NUM_VERTICES; w++) {
    if (!visited[w] && graph[v][w] > 0) {
      visit(w, visited);
    }
  }
}

int connected(void)
{
  char visited[NUM_VERTICES+1];
  int i;

  for (i = 1; i <= NUM_VERTICES; i++) {
    visited[i] = 0;
  }
  for (i = 1; i <= NUM_VERTICES; i++) {
    if (deg[i] > 0) {
      visit(i, visited);
      break;
    }
  }
  for (i = 1; i <= NUM_VERTICES; i++) {
    if (deg[i] > 0 && !visited[i]) {
      return 0;
    }
  }
  return 1;
}

int eulerian(void)
{
  int i;
  for (i = 1; i <= NUM_VERTICES; i++) {
    if (deg[i] % 2 == 1) {
      return 0;
    }
  }
  return connected();
}

int find_tour(int start, int *temp)
{
  int len = 0;
  int next;

  temp[len++] = start;
  while (deg[start] > 0) {
    for (next = 1; next <= NUM_VERTICES; next++) {
      if (graph[start][next] > 0) {
	break;
      }
    }
    temp[len++] = next;
    graph[start][next]--; deg[start]--;
    graph[next][start]--; deg[next]--;
    start = next;
  }
  return len;
}

int graft_tour(int *final, int final_len, int *tour, int tour_len)
{
  int pos[NUM_VERTICES+1];
  int i, j, p1, p2;

  for (i = 1; i <= NUM_VERTICES; i++) {
    pos[i] = -1;
  }
  for (i = 0; i < final_len; i++) {
    pos[final[i]] = i;
  }
  for (i = 0; i < tour_len; i++) {
    if (pos[tour[i]] >= 0) {
      break;
    }
  }
  assert(i < tour_len);
  p1 = pos[tour[i]];
  p2 = i;
  for (i = final_len-1; i > p1; i--) {
    final[i+tour_len-1] = final[i];
  }
  for (i = p2+1, j = 0; i < tour_len-1; i++, j++) {
    final[p1+j+1] = tour[i];
  }
  for (i = 0; i <= p2; i++) {
    final[p1+j+1] = tour[i];
  }

  return final_len+tour_len-1;
}

void eulerian_tour(void)
{
  int final[2000], temp[2000];
  int final_len, temp_len, first_time;
  int i, found;

  final_len = temp_len = 0;
  first_time = 1;

  while (1) {
    found = 0;
    if (first_time) {
      for (i = 1; i <= NUM_VERTICES; i++) {
	if (deg[i] > 0) {
	  found = 1;
	  break;
	}
      }
    } else {
      /* this ensures that we can graft next tour on to existing one */
      for (i = 0; i < final_len; i++) {
	if (deg[final[i]] > 0) {
	  found = 1;
	  break;
	}
      }
      i = final[i];
    }
    if (!found) {
      break;
    }

    if (first_time) {
      final_len = find_tour(i, final);
    } else {
      temp_len = find_tour(i, temp);
      final_len = graft_tour(final, final_len, temp, temp_len);
    }
    first_time = 0;
  }

  for (i = 0; i < final_len-1; i++) {
    printf("%d %d\n", final[i], final[i+1]);
  }
}

int main(void)
{
  int T, N, i, j;
  int u, v;
  
  scanf("%d", &T);
  for (i = 1; i <= T; i++) {
    clear_graph();
    if (i > 1) {
      printf("\n");
    }
    printf("Case #%d\n", i);
    scanf("%d", &N);
    for (j = 0; j < N; j++) {
      scanf("%d %d", &u, &v);
      graph[u][v]++;
      graph[v][u]++;
      deg[u]++;
      deg[v]++;
    }

    if (eulerian()) {
      eulerian_tour();
    } else {
      printf("some beads may be lost\n");
    }
  }
  return 0;
}
