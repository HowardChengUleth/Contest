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

//#define DEBUG 

struct Ant {
  int location;
  int times;
  int id, dist;
  
  void init(int i, int loc) {
    id = i;
    location = loc;
    times = 0;
    dist = 0;
  }

  bool operator<(const Ant &a) const
  {
    return dist < a.dist || (dist == a.dist && id < a.id);
  }

  bool idcmp(const Ant &a) const
  {
    return id < a.id;
  }
};

bool idcmp(const Ant &a1, const Ant &a2)
{
  return a1.id < a2.id;
}

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
    ant[i].init(i, j);
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

void solve_case(void)
{
  int l, bug;
  int Dbug[MAX_N], Pbug[MAX_N];
  int mark[MAX_N], trail[MAX_N];

  cin >> l;

  while (l-- > 0) {
    cin >> bug;

#ifdef DEBUG
    cout << "Bug = " << bug << endl;
#endif
    bug--;
    fill(Dbug, Dbug+n, -1);
    DFS(bug, -1, 0, Dbug, Pbug);

    for (int i = 0; i < k; i++) {
      ant[i].dist = Dbug[ant[i].location];
    }

    sort(ant, ant+k);

    /* now process the ants from the closest one first */
    fill(mark, mark+n, -1);
    for (int i = 0; i < k; i++) {
      int t = 0;
#ifdef DEBUG
      cout << "  Ant " << ant[i].id << " at " << ant[i].location << endl;
#endif
      trail[t] = ant[i].location;
      while (ant[i].location != bug && mark[ant[i].location] < 0) {
	mark[ant[i].location] = t;
	t++;
	ant[i].location = Pbug[ant[i].location];
	trail[t] = ant[i].location;
      }
#ifdef DEBUG
      cout << "mark = " << mark[ant[i].location] << ", loc = "
	   << ant[i].location << endl;
#endif
      if (mark[ant[i].location] < 0) {
	assert(i == 0);
	mark[ant[i].location] = t;
	ant[i].times++;
      } else {
	int ts;
	if (t != mark[ant[i].location]) {
	  ts = mark[ant[i].location];
	} else {
	  ts = mark[ant[i].location]-1;
	}
	ant[i].location = trail[ts++];
	while (ts < t) {
	  mark[trail[ts++]] = -1;
	}
      }
    }

    sort(ant, ant+k, idcmp);

#ifdef DEBUG
    for (int i = 0; i < k; i++) {
      cout << ant[i] << endl;
    }
    cout << "------------" << endl;
#endif
  }
  
  sort(ant, ant+k, idcmp);
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
