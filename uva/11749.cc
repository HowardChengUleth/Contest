// We keep only the heaviest edges and then find the largest
// connected component.

#include <iostream>
#include <algorithm>

using namespace std;

int DFS(bool graph[501][501], int v, int n, bool visited[501])
{
  int total = 1;
  visited[v] = true;

  for (int w = 1; w <= n; w++) {
    if (graph[v][w] && !visited[w]) {
      total += DFS(graph, w, n, visited);
    }
  }
  return total;
}

bool do_case(void)
{
  int n, m;
  cin >> n >> m;
  if (!n && !m) return false;

  int weight[501][501];
  bool graph[501][501];
  for (int i = 1; i <= n; i++) {
    fill(graph[i]+1, graph[i]+n+1, false);
  }

  int max_edge = -1;
  bool max_init = false;
  for (int i = 0; i < m; i++) {
    int u, v, p;
    cin >> u >> v >> p;
    if (!graph[u][v] || p > weight[u][v]) {
      graph[u][v] = graph[v][u] = true;
      weight[u][v] = weight[v][u] = p;
    }
    if (!max_init || p > max_edge) {
      max_edge = p;
      max_init = true;
    }
  }

  for (int u = 1; u <= n; u++) {
    for (int v = 1; v <= n; v++) {
      if (graph[u][v] && weight[u][v] != max_edge) {
	graph[u][v] = graph[v][u] = false;
      }
    }
  }

  bool visited[501];
  fill(visited+1, visited+n+1, false);

  int best = 0;
  for (int i = 1; i <= n; i++) {
    if (visited[i]) continue;
    int count = DFS(graph, i, n, visited);
    if (count > best) {
      best = count;
    }
  }
  cout << best << endl;


  return true;
}

int main(void)
{
  while (do_case())
    ;
  
  return 0;
}
