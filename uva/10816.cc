/*
 * Dijkstra's Algorithm
 *
 * Author: Howard Cheng
 * Reference:
 *   Ian Parberry's "Problems on Algorithms", page 102.
 *
 * Given a weight matrix representing a graph and a source vertex, this
 * algorithm computes the shortest distance, as well as path, to each
 * of the other vertices.  The paths are represented by an inverted list,
 * such that if v preceeds immediately before w in a path from the
 * source to vertex w, then the path P[w] is v.  The distances from
 * the source to v is given in D[v] (DISCONNECT if not connected).
 *
 * Call get_path to recover the path.
 *
 * Note: Dijkstra's algorithm only works if all weight edges are
 *       non-negative.
 *
 */

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_NODES = 101;
const int DISCONNECT = -1;

/* assume that D and P have been allocated */
void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int src, int D[], 
	      int P[])
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

int get_path(int v, int P[], int path[])
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

struct Edge
{
  int u, v, R, D;
};
  
int N, E;
int S, T;
Edge edge[10000];

bool solve(int temp, bool print = false)
{
  int graph[MAX_NODES][MAX_NODES];
  for (int i = 1; i <= N; i++) {
    fill(graph[i], graph[i]+N+1, DISCONNECT);
    graph[i][i] = 0;
  }
  for (int i = 0; i < E; i++) {
    if (edge[i].R <= temp) {
      int u = edge[i].u, v = edge[i].v, D = edge[i].D;
      if (graph[u][v] == DISCONNECT ||
	  graph[u][v] > D) {
	graph[u][v] = graph[v][u] = D;
      }
    }
  }

  int D[MAX_NODES];
  int P[MAX_NODES];
  dijkstra(graph, N+1, S, D, P);

  if (D[T] == DISCONNECT) {
    return false;
  }

  if (print) {
    int path[MAX_NODES];
    int num = get_path(T, P, path);
    for (int i = 0; i < num; i++) {
      if (i) cout << ' ';
      cout << path[i];
    }
    cout << endl;
    cout << D[T]/10 << '.' << D[T]%10 << ' '
	 << temp/10 << '.' << temp%10 << endl;
  }
    
  return true;
}

bool solve()
{
  if (!(cin >> N >> E)) {
    return false;
  }

  cin >> S >> T;

  int lo = 1000;
  int hi = 0;
  for (int i = 0; i < E; i++) {
    cin >> edge[i].u >> edge[i].v;
    int x;
    cin >> x;
    cin.ignore(1);
    cin >> edge[i].R;
    edge[i].R += 10*x;
    cin >> x;
    cin.ignore(1);
    cin >> edge[i].D;
    edge[i].D += 10*x;
    lo = min(edge[i].R, lo);
    hi = max(edge[i].R, hi);
  }
  
  if (solve(lo)) {
    hi = lo;
  }

  while (lo+1 < hi) {
    int mid = (lo+hi)/2;
    if (solve(mid)) {
      hi = mid;
    } else {
      lo = mid;
    }
  }
  
  solve(hi, true);
  
  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}

