#include <iostream>
#include <vector>
using namespace std;

bool check_degrees(int n, const vector<int>& degrees)
{
  for (int i = 0; i < n; i++)
    if (degrees[i] & 1) // vetex i has an odd degree
      return false;
  return true;
}

void dfs(int n, int i, const vector< vector<bool> >& graph,
  vector<bool>& visited)
{
  visited[i] = true;
  const vector<bool>& g = graph[i];
  for (int j = 0; j < n; j++)
    if (g[j] && !visited[j])
      dfs(n, j, graph, visited);
}

bool check_connection(int n, const vector<int>& degrees,
  const vector< vector<bool> >& graph)
{
  // do a depth-first-search and see if all of the vertices are connected
  vector<bool> visited(n, false);
  int start;
  for (start = 0; start < n; start++)
    if (degrees[start])
      break;
  if (start < n)
    dfs(n, start, graph, visited);
  for (int i = 0; i < n; i++)
    if (degrees[i]) {
      if (!visited[i])
        return false;
    }
  return true;
}

int main()
{
  int n, r;
  while (cin >> n >> r) {
    vector<int> degrees(n, 0);
    vector< vector<bool> > graph(n, vector<bool>(n, false));
    for (int i = 0; i < r; i++) {
      int c1, c2;
      cin >> c1 >> c2;
      degrees[c1]++;
      degrees[c2]++;
      graph[c1][c2] = graph[c2][c1] = true;
    }
    if (r && check_degrees(n, degrees) && check_connection(n, degrees, graph))
      cout << "Possible\n";
    else
      cout << "Not Possible\n";
  }
  return 0;
}
