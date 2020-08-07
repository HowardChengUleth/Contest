// The idea is to try T = 0, 1, 2, ..., N-1 until it works.  (Binary search
// also works).
//
// For each T, we have to make sure that each student does not have their
// choices T+1, ..., N-1 in the same class.  Notice that each student only
// has 2 choices so it can be encoded as a binary value.  And the constraints
// that two specific students cannot be in the same class can be coded as
// a boolean constraint NOT(A AND B) = NOT A OR NOT B.  This is a 2-SAT
// problem.


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

#include <iostream>
#include <algorithm>
#include <stack>
#include <cassert>
#include <vector>
using namespace std;

const int MAX_VARS = 200;          // maximum number of variables
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


// Declare this as a global variable if MAX_NODES is large to
//   avoid Runtime Error.
Graph G;

int N;
int C[200];
int prefs[200][200];

// if a student is in:
//
// class 0 -> 1 = T, 2 = F
// class 1 -> 2 = T, 0 = F
// class 2 -> 0 = T, 1 = F

// x and y are in different classes
void add_constraint(int x, int y)
{
  int Tx = (C[x]+1) % 3, Fx = (C[x]+2) % 3;
  int Ty = (C[y]+1) % 3, Fy = (C[y]+2) % 3;
  int vx = VAR(x), vy = VAR(y);
  
  if (Tx == Ty) {
    // NOT (x AND y)
    add_clause(G, NOT(vx), NOT(vy));
  }
  if (Tx == Fy) {
    // NOT (x and NOT y)
    add_clause(G, NOT(vx), vy);
  }
  if (Fx == Ty) {
    // NOT (NOT x and y)
    add_clause(G, vx, NOT(vy));
  }
  if (Fx == Fy) {
    // NOT (NOT x and NOT y)
    add_clause(G, vx, vy);
  }
}

bool works(int T)
{
  G.clear();
  G.numNodes = 2*N;

  for (int i = 0; i < N; i++) {
    for (int j = T; j < N-1; j++) {
      add_constraint(i, prefs[i][j]);
    }
  }

  bool val[MAX_VARS];
  return twoSAT(G, val);
}

int main()
{
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> C[i];
    for (int j = 0; j < N-1; j++) {
      cin >> prefs[i][j];
      prefs[i][j]--;
    }
  }

  for (int T = 0; T <= N-1; T++) {
    if (works(T)) {
      cout << T << endl;
      break;
    }
  }
  return 0;
}

