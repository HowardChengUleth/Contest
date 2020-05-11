/*
 * Min Cost Max Flow for Dense graphs
 *
 * Authors: Frank Chu, Igor Naverniouk
 * http://shygypsy.com/tools/mcmf3.cpp
 *
 * Min cost max flow * (Edmonds-Karp relabelling + Dijkstra)
 *
 * This implementation takes a directed graph where each edge has a
 * capacity ('cap') and a cost per unit of flow ('cost') and returns a
 * maximum flow network of minimal cost ('fcost') from s to t.
 *
 * PARAMETERS:
 *      - cap (global): adjacency matrix where cap[u][v] is the capacity
 *          of the edge u->v. cap[u][v] is 0 for non-existent edges.
 *      - cost (global): a matrix where cost[u][v] is the cost per unit
 *          of flow along the edge u->v. If cap[u][v] == 0, cost[u][v] is
 *          ignored. ALL COSTS MUST BE NON-NEGATIVE!
 *      - n: the number of vertices ([0, n-1] are considered as vertices).
 *      - s: source vertex.
 *      - t: sink.
 * RETURNS:
 *      - the flow
 *      - the total cost through 'fcost'
 *      - fnet contains the flow network. Careful: both fnet[u][v] and
 *          fnet[v][u] could be positive. Take the difference.
 * COMPLEXITY:
 *      - Worst case: O(n^2*flow  <?  n^3*fcost)
 * REFERENCE:
 *      Edmonds, J., Karp, R.  "Theoretical Improvements in Algorithmic
 *          Efficieincy for Network Flow Problems".
 *      This is a slight improvement of Frank Chu's implementation.
 **/

#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

// the maximum number of vertices + 1
const int NN = 103;

// adjacency matrix (fill this up)
long long cap[NN][NN];

// cost per unit of flow matrix (fill this up)
long long cost[NN][NN];

// flow network and adjacency list
int fnet[NN][NN], adj[NN][NN], deg[NN];

// Dijkstra's successor and depth
int par[NN];
long long d[NN];        // par[source] = source;

// Labelling function
long long pi[NN];

const long long Inf = LONG_LONG_MAX/2;

// Dijkstra's using non-negative edge weights (cost + potential)
#define Pot(u,v) (d[u] + pi[u] - pi[v])

bool dijkstra(int n, int s, int t)
{
  for (int i = 0; i < n; i++) {
    d[i] = Inf;
    par[i] = -1;
  }
  
  d[s] = 0;
  par[s] = -n - 1;

  while (1) {
    // find u with smallest d[u]
    int u = -1;
    long long bestD = Inf;
    for (int i = 0; i < n; i++) {
      if (par[i] < 0 && d[i] < bestD) {
	bestD = d[u = i];
      }
    }
    if (bestD == Inf) break;

    // relax edge (u,i) or (i,u) for all i;
    par[u] = -par[u] - 1;
    for (int i = 0; i < deg[u]; i++) {
      // try undoing edge v->u      
      int v = adj[u][i];
      if (par[v] >= 0) continue;
      if (fnet[v][u] && d[v] > Pot(u,v) - cost[v][u]) {
	d[v] = Pot( u, v ) - cost[v][u];
	par[v] = -u-1;
      }
      
      // try edge u->v
      if (fnet[u][v] < cap[u][v] && d[v] > Pot(u,v) + cost[u][v]) {
	d[v] = Pot(u,v) + cost[u][v];
	par[v] = -u - 1;
      }
    }
  }
  
  for (int i = 0; i < n; i++) {
    if (pi[i] < Inf) {
      pi[i] += d[i];
    }
  }
  
  return par[t] >= 0;
}
  
#undef Pot

long long mcmf(int n, int s, int t, long long &fcost)
{
  // build the adjacency list
  fill(deg, deg+NN, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (cap[i][j] || cap[j][i]) {
	adj[i][deg[i]++] = j;
      }
    }
  }
  
  for (int i = 0; i < NN; i++) {
    fill(fnet[i], fnet[i]+NN, 0);
  }
  fill(pi, pi+NN, 0);
  long long flow = fcost = 0;
  
  // repeatedly, find a cheapest path from s to t
  while (dijkstra(n, s, t)) {
    // get the bottleneck capacity
    long long bot = LONG_LONG_MAX;
    for (int v = t, u = par[v]; v != s; u = par[v = u]) {
      bot = min(bot, fnet[v][u] ? fnet[v][u] : (cap[u][v] - fnet[u][v]));
    }
    
    // update the flow network
    for (int v = t, u = par[v]; v != s; u = par[v = u]) {
      if (fnet[v][u]) {
	fnet[v][u] -= bot;
	fcost -= bot * cost[v][u];
      } else {
	fnet[u][v] += bot;
	fcost += bot * cost[u][v];
      }
    }
    
    flow += bot;
  }
  
  return flow;
}

#include <iostream>
using namespace std;


bool solve_case()
{
  int N, M;

  if (!(cin >> N >> M)) {
    return false;
  }

  for (int i = 0; i < N+2; i++) {
    fill(cap[i], cap[i]+N+2, 0);
  }

  int u[5000], v[5000], c[5000];
  for (int i = 0; i < M; i++) {
    cin >> u[i] >> v[i] >> c[i];
  }
  int D, K;
  cin >> D >> K;
  for (int i = 0; i < M; i++) {
    cost[u[i]][v[i]] = c[i];
    cap[u[i]][v[i]] = K;
    cost[v[i]][u[i]] = c[i];
    cap[v[i]][u[i]] = K;
  }
  cost[0][1] = 0;
  cap[0][1] = D;
  cost[N][N+1] = 0;
  cap[N][N+1] = D;

  long long fcost;
  long long flow = mcmf(N+2, 0, N+1, fcost);

  if (flow < D) {
    cout << "Impossible." << endl;
  } else {
    cout << fcost << endl;
  }
  
  return true;
}

int main()
{
  while (solve_case())
    ;
  return 0;
}

