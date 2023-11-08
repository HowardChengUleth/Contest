#include <bits/stdc++.h>

using namespace std;

// SCC code from ULeth code library
//
// Author: Darcy Best
// Date  : October 1, 2010

const int MAX_NODES = 100005;

struct Graph{
  int numNodes;
  map<int,int> adj[MAX_NODES];
  void clear(){
    numNodes = 0;
    for(int i=0;i<MAX_NODES;i++)
      adj[i].clear();
  }
  void add_edge(int u,int v, int strict = 0){
    adj[u][v] = strict;
  }
};

int po[MAX_NODES],comp[MAX_NODES];

void DFS(int v,const Graph& G,Graph& G_scc,int& C,
	 stack<int>& P,stack<int>& S){
  po[v] = C++;
  
  S.push(v);  P.push(v);
  for(auto [w, s] : G.adj[v]) {
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
  
  // You do not need this if you are only interested in the number of
  //    strongly connected components.
  for(int i=0;i<G.numNodes;i++){
    for(auto [w, s] : G.adj[i]) {
      if(comp[i] != comp[w])
	G_scc.add_edge(comp[i],comp[w], s);
    }
  }
  
  return G_scc.numNodes;
}

map<string, int> prob;

int prob_id(const string &s)
{
  if (prob.find(s) == prob.end()) {
    int next = prob.size();
    prob[s] = next;
  }
  return prob[s];
}

typedef pair<int,int> pii;

int M, N;
vector<pii> subseteq, subset;

void read_edge(vector<pii> &S, int N)
{
  S.resize(N);
  for (auto &p : S) {
    string a, b;
    cin >> a >> b;
    p = make_pair(prob_id(a), prob_id(b));
  }
}

Graph G,G_scc;

vector<int> pathlen;

int DFS(int v)
{
  if (pathlen[v] >= 0) {
    return pathlen[v];
  }
  
  pathlen[v] = 1;
  for (auto [w, s] : G_scc.adj[v]) {
    pathlen[v] = max(pathlen[v], s + DFS(w));
  }

  return pathlen[v];
}

int main()
{
  cin >> M >> N;
  read_edge(subseteq, M);
  read_edge(subset, N);

  // max number is basically the number of SCCs of the graph
  // consisting of only the subseteq edges
  G.clear();
  G.numNodes = prob.size();
  for (auto [a, b] : subseteq) {
    G.add_edge(a, b);
  }
  int num_scc = SCC(G, G_scc);

  // to get the min number, we look at the G_scc and add the strict edges
  // to have weight 1
  for (auto [a, b] : subset) {
    G_scc.add_edge(comp[a], comp[b], 1);
  }

  pathlen.resize(num_scc, -1);
  for (int i = 0; i < num_scc; i++) {
    DFS(i);
  }

  cout << *max_element(begin(pathlen), end(pathlen)) << " " << num_scc << endl;
  
  return 0;
}
