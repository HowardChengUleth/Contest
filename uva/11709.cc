#include <iostream>
#include <algorithm>
#include <stack>
#include <cassert>
#include <vector>
using namespace std;

const int MAX_NODES = 1000;

struct Graph{
  int numNodes;
  vector<int> adj[MAX_NODES];
  void clear(){
    numNodes = 0;
    for(int i=0;i<MAX_NODES;i++)
      adj[i].clear();
  }
  void add_edge(int u,int v){
    if(find(adj[u].begin(),adj[u].end(),v) == adj[u].end())
      adj[u].push_back(v);
  }
};

int po[MAX_NODES],comp[MAX_NODES];

void DFS(int v,const Graph& G,Graph& G_scc,int& C,
	 stack<int>& P,stack<int>& S){
  po[v] = C++;
  
  S.push(v);  P.push(v);
  for(unsigned int i=0;i<G.adj[v].size();i++){
    int w = G.adj[v][i];
    if(po[w] == -1){
      DFS(w,G,G_scc,C,P,S);
    } else if(comp[w] == -1){
      while(!P.empty() && (po[P.top()] > po[w]))
	P.pop();
    }
  }
  if(!P.empty() && P.top() == v){
    while(!S.empty()){
      int t = S.top();
      S.pop();
      comp[t] = G_scc.numNodes;
      if(t == v)
	break;
    }
    G_scc.numNodes++;
    P.pop();
  }
}

int SCC(const Graph& G,Graph& G_scc){
  G_scc.clear();
  int C=1;
  stack<int> P,S;
  fill(po,po+G.numNodes,-1);
  fill(comp,comp+G.numNodes,-1);
  for(int i=0;i<G.numNodes;i++)
    if(po[i] == -1)
      DFS(i,G,G_scc,C,P,S);
  
  return G_scc.numNodes;
}

// Declare these as a global variable if MAX_NODES is large to
//   avoid Runtime Error.
Graph G,G_scc;

#include <map>
#include <string>

bool solve()
{
  int n, m;
  cin >> n >> m;
  if (!n && !m) return false;

  G.clear();
  G.numNodes = n;
  map<string, int> names;

  cin.ignore(1);
  for (int i = 0; i < n; i++) {
    string s;
    getline(cin, s);
    names[s] = i;
  }

  for (int i = 0; i < m; i++) {
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    G.add_edge(names[s1], names[s2]);
  }
  cout << SCC(G, G_scc) << endl;

  return true;
}

int main(){
  while (solve())
    ;
  return 0;
}
