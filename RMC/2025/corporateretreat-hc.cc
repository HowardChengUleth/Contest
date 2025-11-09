#include <bits/stdc++.h>

using namespace std;

// 2SAT solver: returns T/F whether it is satisfiable -- O(n+m)
//   - use NOT() to negate a variable (works on negated ones too!)
//   - ALWAYS use VAR() to talk about the non-negated version of the var i
//   - use add_clause to add a clause
//   - one possible satisfying assignment is returned in val[], if
//     it exists
//   - To FORCE i to be true:  add_clause(G,VAR(i),VAR(i));
//   - To implement XOR -- say (i XOR j) :
//      add_clause(G,VAR(i),VAR(j)); add_clause(G,NOT(VAR(i)),NOT(VAR(j)));
//     NOTE: val[] is indexed by i for var i, not by VAR(i)!!!

#include <cassert>
using namespace std;

const int MAX_VARS = 1000;          // maximum number of variables
const int MAX_NODES = 2*MAX_VARS;

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
int num_scc;

void DFS(int v, const Graph& G, int& C, stack<int>& P,stack<int>& S){
  po[v] = C++;
  
  S.push(v);  P.push(v);
  for(unsigned int i=0;i<G.adj[v].size();i++){
    int w = G.adj[v][i];
    if(po[w] == -1){
      DFS(w,G,C,P,S);
    } else if(comp[w] == -1){
      while(!P.empty() && (po[P.top()] > po[w]))
	P.pop();
    }
  }
  if(!P.empty() && P.top() == v){
    while(!S.empty()){
      int t = S.top();
      S.pop();
      comp[t] = num_scc;
      if(t == v)
	break;
    }
    P.pop();
    num_scc++;
  }
}

int SCC(const Graph& G){
  num_scc = 0;
  int C = 1;
  stack<int> P,S;
  fill(po,po+G.numNodes,-1);
  fill(comp,comp+G.numNodes,-1);
  for(int i=0;i<G.numNodes;i++)
    if(po[i] == -1)
      DFS(i,G,C,P,S);
  
  return num_scc;
}


int VAR(int i) { return 2*i; }
int NOT(int i) { return i ^ 1; }

void add_clause(Graph &G, int v, int w) { // adds (v || w)
  if (v == NOT(w)) return;
  G.add_edge(NOT(v), w);
  G.add_edge(NOT(w), v);
}

bool twoSAT(const Graph &G, bool val[]) {   // assumes graph is built
  SCC(G);
  for (int i = 0; i < G.numNodes; i += 2) {
    if (comp[i] == comp[i+1]) return false;
    val[i/2] = (comp[i] < comp[i+1]);
  }
  return true;
}


Graph G;

typedef pair<int,int> pii;

int N, K, M;

set<pii> conflict;

bool check_rest(vector<int> &colour)
{
  vector<int> num_colours(N);
  vector<vector<int>> candidate_colours(N);

  // probably not needed...
  for (int i = 0; i < K; i++) {
    num_colours[i] = 1;
    candidate_colours[i].push_back(colour[i]);
  }

  for (int i = K; i < N; i++) {
    bool bad[4] = {false};
    for (int j = 0; j < K; j++) {
      if (conflict.count(pii(i, j))) {
	bad[colour[j]] = true;
      }
    }

    for (int c = 1; c <= 3; c++) {
      if (!bad[c]) {
	num_colours[i]++;
	candidate_colours[i].push_back(c);
      }
    }
    if (num_colours[i] == 0) {
      return false;
    }
  }

  // check to make sure all the forced colours are okay
  for (auto [i,j] : conflict) {
    if (num_colours[i] == 1 && num_colours[j] == 1 &&
	candidate_colours[i][0] == candidate_colours[j][0]) {
      return false;
    }
  }

  // var[i] = true if we use first colour, var[i] = false if we use 2nd
  // colour.  Only worry about those that have 2 candidates
  G.clear();
  G.numNodes = 2*N;
  for (int i = 0; i < N; i++) {
    // only one colour: force to use first colour
    if (num_colours[i] == 1) {
      add_clause(G, VAR(i), VAR(i));
    }
  }

  for (auto [i,j] : conflict) {
    if (num_colours[i] == 1 && num_colours[j] == 1)
      continue;
    if (i >= j)
      continue;
    for (int c1 = 0; c1 < num_colours[i]; c1++) {
      for (int c2 = 0; c2 < num_colours[j]; c2++) {
	if (candidate_colours[i][c1] == candidate_colours[j][c2]) {
	  int var1 = (c1 == 0) ? VAR(i) : NOT(VAR(i));
	  int var2 = (c2 == 0) ? VAR(j) : NOT(VAR(j));

	  // !(var1 && var2)
	  add_clause(G, NOT(var1), NOT(var2));
	}
      }
    }
  }

  bool val[MAX_VARS];
  if (twoSAT(G, val)) {
    for (int i = 0; i < N; i++) {
      colour[i] = val[i] ? candidate_colours[i][0] : candidate_colours[i][1];
    }
    return true;
  } else {
    return false;
  }
}

bool colour_execs(vector<int> &colour, int index)
{
  if (index >= K) {
    return check_rest(colour);
  } else {
    for (int c = 1; c <= 3; c++) {
      bool bad = false;
      for (int i = 0; i < index; i++) {
	bad |= (conflict.count(pii(i, index)) && colour[i] == c);
      }

      colour[index] = c;
      if (colour_execs(colour, index+1)) {
	return true;
      }
    }
  }
  return false;
}

int main()
{
  cin >> N >> K >> M;

  for (int k = 0; k < M; k++) {
    int i, j;
    cin >> i >> j;
    conflict.emplace(i-1, j-1);
    conflict.emplace(j-1, i-1);
  }

  vector<int> colour(N);
  if (colour_execs(colour, 0)) {
    cout << "possible" << endl;
    for (auto c : colour) {
      cout << c << ' ';
    }
    cout << endl;
  } else {
    cout << "impossible" << endl;
  }

  return 0;
}
