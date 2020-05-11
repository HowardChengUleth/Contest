#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 26*26;

int node_num(const string &s)
{
  return (s[0] - 'A')*26 + s[1] - 'A';
}

void print_name(int num)
{
  char first = num/26 + 'A',
    second = num%26 + 'A';
  cout << first << second;
}

bool read_graph(bool G[N][N])
{
  int m;

  if (!(cin >> m)) {
    return false;
  }
  
  for (int i = 0; i < N; i++) {
    fill(G[i], G[i]+N, false);
    G[i][i] = true;
  }

  string u, v;
  while (m -- > 0) {
    cin >> u >> v;

    int u_num = node_num(u), v_num = node_num(v);
    G[u_num][v_num] = G[v_num][u_num] = true;
  }
  return true;
}

void solve(bool G[N][N])
{
  string src, dest;
  cin >> src >> dest;

  int src_num = node_num(src), dest_num = node_num(dest);
  
  bool visited[N];
  fill(visited, visited+N, false);

  int succ[N];
  fill(succ, succ+N, -1);

  queue<int> q;
  q.push(dest_num);
  visited[dest_num] = true;

  while (!q.empty()) {
    int v = q.front();
    q.pop();
    if (v == src_num) {
      break;
    }
    
    for (int w = 0; w < N; w++) {
      if (G[v][w] && !visited[w]) {
	q.push(w);
	visited[w] = true;
	succ[w] = v;
      }
    }
  }

  if (succ[src_num] == -1) {
    cout << "No route" << endl;
    return;
  }

  while (src_num != dest_num) {
    print_name(src_num);
    cout << ' ';
    print_name(succ[src_num]);
    cout << endl;
    src_num = succ[src_num];
  }
}

int main(void)
{
  bool G[N][N];
  bool first = true;

  while (read_graph(G)) {
    if (!first) {
      cout << endl;
    }
    first = false;
    solve(G);
  }
  return 0;
}
