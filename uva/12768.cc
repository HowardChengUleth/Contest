//  What is given is a graph.  If you negate all the given weights, you are
//  looking for the shortest (most negative) path from node 1 to anywhere
//  else.  The only tricky part is that if there is a negative cycle that is
//  reachable from node 1, then you can go around this cycle as many times
//  as you want and get an unlimited amount.
//
//  Of course you have to remember to negate the result, and only check for
//  negative cycles reachable from node 1.  Unreachable negative cycles are
//  not important.
//
//  Complexity: O(n^3)
//
//

/*
 * Bellman-Ford Shortest Path Algorithm
 *
 * Author: Howard Cheng
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
 * Note: the Bellman-Ford algorithm has complexity O(n^3), but it works even
 *       when edges have negative weights.  As long as there are no negative
 *       cycles the computed results are correct.
 *
 *       We can make this O(n*m) if we use an adjacency list representation.
 *
 *       This works for directed graphs too.
 *
 *       You can use this to detect negative cycles too.  See code.
 *
 */

#include <iostream>
#include <climits>
#include <cassert>
#include <algorithm>

using namespace std;

const int MAX_NODES = 100;
const int DISCONNECT = INT_MAX;

bool bellmanford(int graph[MAX_NODES][MAX_NODES], int n, int src,
		 int D[])
{
  int v, w, k;

  for (v = 0; v < n; v++) {
    D[v] = INT_MAX;
  }
  D[src] = 0;

  for (k = 0; k < n-1; k++) {
    for (v = 0; v < n; v++) {
      for (w = 0; w < n; w++) {
	if (graph[v][w] != DISCONNECT && D[v] != INT_MAX) {
	  if (D[w] == INT_MAX || D[w] > D[v] + graph[v][w]) {
	    D[w] = D[v] + graph[v][w];
	  }
	}
      }
    }
  }

  /* the following loop is used only to detect negative cycles, not */
  /* needed if you don't care about this                            */
  for (v = 0; v < n; v++) {
    for (w = 0; w < n; w++) {
      if (graph[v][w] != DISCONNECT && D[v] != INT_MAX) {
        if (D[w] == INT_MAX || D[w] > D[v] + graph[v][w]) {
	  /* if we get here then there is a negative cycle somewhere */
	  /* on the path from src to                                 */
	  return true;
	}
      }
    }
  }
  return false;
}

int main(void)
{
  int N, M;
  cin >> N >> M;

  int graph[MAX_NODES][MAX_NODES];

  /* clear graph */
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      graph[i][j] = DISCONNECT;
    }
  }

  for (int i = 0; i < M; i++) {
    int A, B, F;
    cin >> A >> B >> F;
    graph[A-1][B-1] = -F;
  }

  int D[MAX_NODES];
  
  if (bellmanford(graph, N, 0, D)) {
    cout << "Unlimited!" << endl;
  } else {
    cout << -(*min_element(D, D+N)) << endl;
  }

  return 0;
}
