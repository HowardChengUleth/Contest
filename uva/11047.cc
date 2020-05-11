/*
 * Floyd's Algorithm
 *
 * Author: Howard Cheng
 *
 * The following code takes a graph stored in an adjacency matrix "graph",
 * and returns the shortest distance from node i to node j in dist[i][j].
 * We assume that the weights of the edges is not DISCONNECT, and the
 * DISCONNECT constant is used to indicate the absence of an edge.
 *
 * Call extract_path to return the path, as well as its length (in terms
 * of vertices).  The length is -1 if no such path exists.
 *
 */

#include <iostream>
#include <cassert>

using namespace std;

const int MAX_NODES = 100;
const int DISCONNECT = -1;

int graph[MAX_NODES][MAX_NODES];
int dist[MAX_NODES][MAX_NODES];
int inter[MAX_NODES][MAX_NODES];

string loc[MAX_NODES];

void floyd(int n)
{
  int i, j, k;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      dist[i][j] = graph[i][j];
      inter[i][j] = -1;
    }
  }

  for (k = 0; k < n; k++) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
        if (dist[i][k] != DISCONNECT && dist[k][j] != DISCONNECT) {
          int temp = dist[i][k] + dist[k][j];
          if (dist[i][j] == DISCONNECT || dist[i][j] > temp) {
            dist[i][j] = temp;
	    inter[i][j] = k;
	  }
        }
      }
    }
  }
}


#include <algorithm>
#include <string>
#include <cassert>

void print_inter(int s, int t)
{
  if (inter[s][t] < 0) return;
  int k = inter[s][t];
  print_inter(s, k);
  cout << ' ' << loc[k];
  print_inter(k, t);
}

void solve()
{
  int P;
  cin >> P;

  for (int i = 0; i < P; i++) {
    cin >> loc[i];
    fill(graph[i], graph[i]+P, DISCONNECT);
  }

  for (int i = 0; i < P; i++) {
    for (int j = 0; j < P; j++) {
      int C;
      cin >> C;
      if (C >= 0) {
	graph[i][j] = C;
      }
    }
  }

  floyd(P);

  int R;
  cin >> R;
  while (R--) {
    string name, start, end;
    cin >> name >> start >> end;
    int s = find(loc, loc+P, start) - loc;
    int t = find(loc, loc+P, end) - loc;
    if (dist[s][t] == DISCONNECT) {
      cout << "Sorry Mr " << name << " you can not go from " << start
	   << " to " << end << endl;
    } else {
      cout << "Mr " << name << " to go from " << start << " to " << end
	   << ", you will receive " << dist[s][t] << " euros" << endl;
      cout << "Path:" << start;
      print_inter(s, t);
      cout << " " << end << endl;
    }
  }
}

int main()
{
  int C;
  cin >> C;
  while (C--) {
    solve();
  }
  return 0;
}
