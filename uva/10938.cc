#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_N = 5000;
int n;
pair<int,int> edge[2*MAX_N-2];
pair<int,int> G[MAX_N];    /* first = start of entries
                              second = one past the end */


int read_graph(void)
{
  cin >> n;
  if (!n) {
    return 0;
  }

  int u, v, k;
  k = 0;
  for (int i = 0; i < n-1; i++) {
    cin >> u >> v;
    u--; v--;
    edge[k++] = make_pair<int,int>(u, v);
    edge[k++] = make_pair<int,int>(v, u);
  }
  sort(edge, edge + 2*(n-1));
  
  k = 0;
  for (int i = 0; i < n; i++) {
    G[i].first = k;
    while (k < 2*(n-1) && edge[k].first == i)
      k++;
    G[i].second = k;
  }

  return 1;
}

bool DFS(int u, int dist, int *Du, int *Dv, int v)
{
  Du[u] = dist;
  if (u == v) {
    Dv[v] = 0;
    return true;
  }
  for (int i = G[u].first; i != G[u].second; ++i) {
    if (Du[edge[i].second] < 0) {
      if (DFS(edge[i].second, dist+1, Du, Dv, v)) {
	Dv[u] = Du[v] - dist;
	return true;
      }
    }
  }
  return false;
}

void solve_case(int u, int v)
{
  int Du[MAX_N], Dv[MAX_N];
  int p, r;

  fill(Du, Du+n, -1);
  fill(Dv, Dv+n, -1);
  DFS(u, 0, Du, Dv, v);

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
    assert(p > 0 && r > 0);

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
