/* @JUDGE_ID: 1102NT 280 C++ "" */

#include <iostream>

using namespace std;

const int MAX_VERTEX = 100;
typedef char Graph[MAX_VERTEX][MAX_VERTEX];

void clear_graph(Graph g, int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      g[i][j] = 0;
    }
  }
}

int read_graph(Graph g)
{
  int n, u, v;

  cin >> n;
  clear_graph(g, n);
  if (n > 0) {
    while (cin >> u && u != 0) {
      while (cin >> v && v != 0) {
	g[u-1][v-1] = 1;
      }
    }
  }
  return n;
}

void floyd(Graph g, int n)
{
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	g[i][j] |= g[i][k] && g[k][j];
      }
    }
  }
}

void solve(Graph g, int n, int v)
{
  int count = 0;
  
  for (int i = 0; i < n; i++) {
    if (!g[v][i]) {
      count++;
    }
  }

  cout << count;
  for (int i = 0; i < n; i++) {
    if (!g[v][i]) {
      cout << " " << i+1;
    }
  }
  cout << endl;

}

int main(void)
{
  Graph g;
  int n, q, start;

  while (n = read_graph(g)) {
    floyd(g, n);
    cin >> q;
    while (q-- > 0) {
      cin >> start;
      solve(g, n, start-1);
    }
  }
  return 0;
}
