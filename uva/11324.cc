//
// The idea is this:
//
// 1. Find all strongly connected components (SCC): largest components
//    in which there is a directed path from each vertex to any other
//    vertex in the same component.
//
// 2. Form a directed graph of SCCs.  This graph is guaranteed to be
//    acyclic.  The weight of each vertex is the size of the SCC.
//
// 3. Look for the heaviest path in this new graph (use dynamic programming).
//    This works because there are no cycles.
//

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

#define VI vector<int>
#define MAXN 1000

VI g[MAXN], curr;
vector< VI > scc;
int dfsnum[MAXN], low[MAXN], id;
char done[MAXN];
char adj[MAXN][MAXN];

VI sg[MAXN];          /* graph of strongly connected components */

int best[MAXN];

// SCC can be computed by DFS.  Read a book on algorithms.
void visit(int x){
  curr.push_back(x);
  dfsnum[x] = low[x] = id++;
  for(size_t i = 0; i < g[x].size(); i++)
    if(dfsnum[g[x][i]] == -1){
      visit(g[x][i]);
      if (low[x] > low[g[x][i]]) {
	low[x] = low[g[x][i]];
      }
    } else if(!done[g[x][i]]) {
      if (low[x] > dfsnum[g[x][i]]) {
	low[x] = dfsnum[g[x][i]];
      }
    }

  if(low[x] == dfsnum[x]){
    VI c; int y;
    do{
      done[y = curr[curr.size()-1]] = 1;
      c.push_back(y);
      curr.pop_back();
    } while(y != x);
    scc.push_back(c);
  }
}

void strong_conn(int n){
  memset(dfsnum, -1, n*sizeof(int));
  memset(done, 0, sizeof(done));
  scc.clear(); curr.clear();
  for(int i = id = 0; i < n; i++)
    if(dfsnum[i] == -1) visit(i);
}

// determine if SCC v1 should be connected to SCC v2
bool connected(vector<int> &v1, vector<int> &v2)
{
  for (unsigned int i = 0; i < v1.size(); i++) {
    for (unsigned int j = 0; j < v2.size(); j++) {
      if (adj[v1[i]][v2[j]]) {
	return true;
      }
    }
  }
  return false;
}

// compute heaviest path by dynamic programming: the heaviest path from v
// is simply v's weight + the weight of the heaviest path starting from a
// child of v
void compute(int v)
{
  if (best[v] > 0) {
    return;
  }

  best[v] = scc[v].size();

  for (unsigned int i = 0; i < sg[v].size(); i++) {
    if (sg[v][i] == v) continue;
    compute(sg[v][i]);
    if ((int)scc[v].size() + best[sg[v][i]] > best[v]) {
      best[v] = scc[v].size() + best[sg[v][i]];
    }
  }
}

int main(){
  unsigned int n, m, x, y;
  unsigned int i, j;
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    while(scanf("%d %d", &n, &m) == 2){
      for(i = 0; i < n; i++) {
	g[i].clear();
	for (j = 0; j < n; j++) {
	  adj[i][j] = 0;
	}
	adj[i][i] = 1;
      }

      for(i = 0; i < m; i++){
	scanf("%d %d", &x, &y);
	x--;  y--;
	g[x].push_back(y);
	adj[x][y] = 1;
      }
      strong_conn(n);
      for(i = 0; i < scc.size(); i++){
	sg[i].clear();
	for (j = 0; j < scc.size(); j++) {
	  if (connected(scc[i], scc[j])) {
	    sg[i].push_back(j);
	  }
	}
      }

      fill(best, best+scc.size(), -1);
      int largest = 0;
      for (i = 0; i < scc.size(); i++) {
	compute(i);
	if (best[i] > largest) {
	  largest = best[i];
	}
      }
      printf("%d\n", largest);
    }
  }
  return 0;
}
