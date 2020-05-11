#include <stdio.h>

#include <stdlib.h>
#include <assert.h>

#define MAX_NODES 26*26
#define DISCONNECT -1

/* assume that D and P have been allocated */
void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int src, int *D, int *P)
{
  char used[MAX_NODES];
  int fringe[MAX_NODES];
  int f_size;
  int v, w, j, wj;
  int best, best_init;

  f_size = 0;
  for (v = 0; v < n; v++) {
    if (graph[src][v] != DISCONNECT && src != v) {
      D[v] = graph[src][v];
      P[v] = src;
      fringe[f_size++] = v;
      used[v] = 1;
    } else {
      D[v] = DISCONNECT;
      P[v] = -1;
      used[v] = 0;
    }
  }
  D[src] = 0;
  P[src] = -1;
  used[src] = 1;

  best_init = 1;
  while (best_init) {
    /* find unused vertex with smallest D */
    best_init = 0;
    for (j = 0; j < f_size; j++) {
      v = fringe[j];
      assert(D[v] != DISCONNECT);
      if (!best_init || D[v] < best) {
        best = D[v];
        w = v;
        wj = j;
        best_init = 1;
      }
    }

    if (best_init) {
      assert(D[w] != DISCONNECT);
      assert(fringe[wj] == w);

      /* get rid of w from fringe */
      f_size--;
      for (j = wj; j < f_size; j++) {
        fringe[j] = fringe[j+1];
      }

      /* update distances and add new vertices to fringe */
      for (v = 0; v < n; v++) {
        if (v != src && graph[w][v] != DISCONNECT) {
          if (D[v] == DISCONNECT || D[w] + graph[w][v] < D[v]) {
            D[v] = D[w] + graph[w][v];
            P[v] = w;
          } else if (D[w] + graph[w][v] == D[v]) {
            /* put tie-breaker here */
          }
          if (!used[v]) {
            used[v] = 1;
            fringe[f_size++] = v;
          }
        }
      }
    }
  }
  D[src] = 0;
}

int get_path(int v, int *P, int *path)
{
  int A[MAX_NODES];
  int i, k;

  k = 0;
  A[k++] = v;
  while (P[v] != -1) {
    v = P[v];
    A[k++] = v;
  }
  for (i = k-1; i >= 0; i--) {
    path[k-1-i] = A[i];
  }
  return k;
}

#define INDEX(route,station) ((route-'A')*26+(station)-'a')
#define ROUTE(index) ((index)/26 + 'A')
#define STATION(index) ((index)%26 + 'a')


int G[MAX_NODES][MAX_NODES];
int routes;

void clear_graph(void)
{
  int i, j;

  for (i = 0; i < MAX_NODES; i++) {
    for (j = 0; j < MAX_NODES; j++) {
      G[i][j] = DISCONNECT;
    }
  }
}

void add_edge(char r1, char s1, char r2, char s2, int w)
{
  G[INDEX(r1, s1)][INDEX(r2, s2)] = w;
  G[INDEX(r2, s2)][INDEX(r1, s1)] = w;
}

void parse_route(char *line)
{
  char r;
  int i;
  char prev, curr;

  r = *line++;
  line++;         /* skip : */
  
  for (i = 0; line[i] != '\n'; i++) {
    curr = line[i];
    if (i > 0) {
      add_edge(r, prev, r, curr, 1);
    }
    while (line[i+1] == '=') {
      add_edge(r, curr, line[i+2], line[i+3], 3);
      i += 3;
    }

    prev = curr;
  }
}

void connect_closure(void)
{
  int k, i, j;

  for (k = 0; k < MAX_NODES; k++) {
    for (i = 0; i < MAX_NODES; i++) {
      if (G[i][k] != 3) continue;
      for (j = 0; j < MAX_NODES; j++) {
	if (G[k][j] != 3) continue;
	G[i][j] = 3;
      }
    }
  }
}

int main(void)
{
  int i;
  char line[1024];
  int src, dest;
  int D[MAX_NODES], P[MAX_NODES];
  int path[MAX_NODES];
  int path_len;
  char prev_route;

  clear_graph();
  scanf("%d\n", &routes);
  for (i = 0; i < routes; i++) {
    fgets(line, 1024, stdin);
    parse_route(line);
  }
  connect_closure();
  while (scanf("%s", line) == 1 && line[0] != '#') {
    src = INDEX(line[0], line[1]);
    dest = INDEX(line[2], line[3]);

    dijkstra(G, MAX_NODES, src, D, P);
    printf("%3d: ", D[dest]);

    path_len = get_path(dest, P, path);
    prev_route = ' ';
    for (i = 0; i < path_len; i++) {
      if (prev_route != ROUTE(path[i])) {
	if (i) {
	  putchar('=');
	}
	putchar(ROUTE(path[i]));
      }
      putchar(STATION(path[i]));
      prev_route = ROUTE(path[i]);
    }
    printf("\n");
  }
  
  return 0;
}
