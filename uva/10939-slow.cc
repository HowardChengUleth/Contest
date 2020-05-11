#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_N = 5000;
const int MAX_K = 1000;
const int MAX_L = 500;

int n, k, l;
pair<int,int> edge[2*MAX_N-2];
pair<int,int> G[MAX_N];    /* first = start of entries
                              second = one past the end */

struct Ant {
  int location;
  int times;
  
  void init(int loc) {
    location = loc;
    times = 0;
  }

  void move(int *Pbug)
  {
    location = Pbug[location];
  }
};

ostream &operator<<(ostream &os, const Ant &ant)
{
  return os << ant.location+1 << ' ' << ant.times;
}

Ant ant[MAX_K];


int read_graph(void)
{
  cin >> n;
  if (!n) {
    return 0;
  }

  int u, v, j;
  j = 0;
  for (int i = 0; i < n-1; i++) {
    cin >> u >> v;
    u--; v--;
    edge[j++] = make_pair<int,int>(u, v);
    edge[j++] = make_pair<int,int>(v, u);
  }
  sort(edge, edge + 2*(n-1));
  
  j = 0;
  for (int i = 0; i < n; i++) {
    G[i].first = j;
    while (j < 2*(n-1) && edge[j].first == i)
      j++;
    G[i].second = j;
  }

  cin >> k;
  for (int i = 0; i < k; i++) {
    cin >> j;
    j--;
    ant[i].init(j);
  }
  return 1;
}

void DFS(int u, int parent, int dist, int *Du, int *Pu)
{
  Du[u] = dist;
  Pu[u] = parent;
  for (int i = G[u].first; i != G[u].second; ++i) {
    if (Du[edge[i].second] < 0) {
      DFS(edge[i].second, u, dist+1, Du, Pu);
    }
  }
}

bool clear_route(int i, int *Dbug, int *Pbug)
{
  i = Pbug[i];
  for (int j = 0; j < k; j++) {
    if (ant[j].location == i) {
      return false;
    }
  }
  return (!Dbug[i] || clear_route(i, Dbug, Pbug));
}

void solve_case(void)
{
  int l, bug;
  int Dbug[MAX_N], Pbug[MAX_N];
  bool moving[MAX_K];
  bool done;

  cin >> l;

  while (l-- > 0) {
    cin >> bug;
    bug--;
    fill(Dbug, Dbug+n, -1);
    DFS(bug, -1, 0, Dbug, Pbug);

    int a;
    fill(moving, moving+k, true);
    done = false;
    for (int i = 0; i < k; i++) {
      if (ant[i].location == bug) {
	a = i;
	done = true;
      }
    }

    while (!done) {
      for (int i = 0; i < k; i++) {
	if (moving[i]) {
	  if (clear_route(ant[i].location, Dbug, Pbug)) {
	    ant[i].move(Pbug);
	    if (ant[i].location == bug) {
	      a = i;
	      done = true;
	      break;
	    }
	  } else {
	    moving[i] = false;
	  }
	}
      }
    }
    ant[a].times++;
  }
  
  for (int i = 0; i < k; i++) {
    cout << ant[i] << endl;
  }
}

int main(void)
{
  while (read_graph()) {
    solve_case();
  }
  return 0;
}
