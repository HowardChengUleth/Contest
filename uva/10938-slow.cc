#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_N = 5000;
int n;
vector<int> adj[MAX_N];

int read_graph(void)
{
  cin >> n;
  if (!n) {
    return 0;
  }
  for (int i = 0; i < n; i++) {
    adj[i].clear();
  }

  int u, v;
  for (int i = 0; i < n-1; i++) {
    cin >> u >> v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  return 1;
}

void DFS(int u, int dist, int *D)
{
  D[u] = dist;
  for (vector<int>::const_iterator it = adj[u].begin(); it != adj[u].end(); 
       ++it) {
    if (D[*it] < 0) {
      DFS(*it, dist+1, D);
    }
  }
}

void solve_case(int u, int v)
{
  int Du[MAX_N], Dv[MAX_N];
  int p, r;

  fill(Du, Du+n, -1);
  fill(Dv, Dv+n, -1);
  DFS(u, 0, Du);
  DFS(v, 0, Dv);

  p = r = -1;
  if (Du[v] % 2 == 0) {
    for (int i = 0; i < n; i++) {
      if (Du[i] == Du[v] / 2 && Dv[i] == Du[v] / 2) {
	p = i+1;
	break;
      }
    }
    assert(p > 0);
    cout << "The fleas meet at " << p << "." << endl;
  } else {
    for (int i = 0; i < n; i++) {
      if (Du[i] == Du[v] / 2 && Dv[i] == Du[v] / 2 + 1) {
	assert(p < 0);
	p = i+1;
      }
      if (Du[i] == Du[v] / 2 + 1 && Dv[i] == Du[v] / 2) {
	assert(r < 0);
	r = i+1;
      }
    }
    if (p > r) {
      swap(p, r);
    }

    cout << "The fleas jump forever between " << p << " and " << r 
	 << "." << endl;
  }
}

int main(void)
{
  while (read_graph()) {
    int l, u, v;
    cin >> l;
    while (l-- > 0) {
      cin >> u >> v;
      solve_case(u-1, v-1);
    }
  }
  return 0;
}
