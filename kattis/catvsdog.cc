#include <bits/stdc++.h>

//
// Make a graph with voters as nodes, and connect two voters if they
// cannot be both satisfied: i.e. there is a pet that one wants to
// keep and one wants to eliminate.  Noticed that a cat lover can
// never be connected to a cat lover and similarly for dog lovers.  So
// this graph is bipartite.
//
// Now we are looking for a maximum independent set.  That is the
// complement of a minimum vertex cover, which has the same size as
// the maximum matching in a bipartite graph.  So the answer can be found
// by computing the maximum matching.

using namespace std;

// Unweighted Bipartite Matching (Undirected Only) -- O(m*sqrt(n))
//  -- Your match is stored in "mate". (mate == -1 if there is no match)
//  -- adj is an adjacency list that indexes the other set
//         Ex: U[0].adj[0] == x means there is an edge from U[0] to V[x]

struct Node{ vector<int> adj; int mate,pred; }; // Ignore "pred" -- For internal use.

void add_edge(Node U[],int u_node,Node V[],int v_node){
  U[u_node].adj.push_back(v_node);
  V[v_node].adj.push_back(u_node);  
}

// u is the number of elements in U
// v is the number of elements in V
int match(Node U[],int u,Node V[],int v){
  for(int i=0;i<u;i++) U[i].mate = -1;
  for(int i=0;i<v;i++) V[i].mate = -1;
  
  int numMatches = 0;
  while(true){
    queue<int> q1,q2;
    for(int i=0;i<u;i++) if(U[i].mate == -1) q1.push(i);
    for(int i=0;i<u;i++) U[i].pred = -1;
    for(int i=0;i<v;i++) V[i].pred = -1;
    
    while(!q1.empty()){
      int x = q1.front(); q1.pop();
      for(int i=0;i<U[x].adj.size();i++){ int w = U[x].adj[i];
	if(V[w].pred != -1) continue;
	if(V[w].mate == -1) V[w].pred = x , q2.push(w);
	else if(V[w].mate != x && U[V[w].mate].pred == -1)
	  V[w].pred = x , U[V[w].mate].pred = w , q1.push(V[w].mate); 
      }
    }

    if(q2.empty()) break;
    while(!q2.empty()){
      Node* W = V; int i,x = q2.front(); q2.pop();
      for(i = x;i >= 0;W=(W == U ? V : U)) i = W[i].pred;
      if(i == -2) continue; numMatches++;
      for(i = x;i >= 0;){
	int p = V[i].pred;  V[i].pred = -2;  V[i].mate = p;
	U[p].mate = i;      i = U[p].pred;   U[p].pred = -2;
      }
    }
  }
  return numMatches;
}

// Other interesting things: (Don't forget about vertices of degree 0)
//  - Minimum Vertex Cover (size == maximum matching cardinality -- Konig's Thm)
//  - Maximum Independent Set (Complement of minimum vertex cover -- see code)
//  - Minimum Edge Cover (size == max indep. set): Take all edges in the matching +
//    for every node (in U and V) that does not have a mate, include ANY adjacent edge

int vertex_cover(Node U[],int u,Node V[],int v,
		 vector<int>& coverU,vector<int>& coverV){
  coverU.clear(); coverV.clear(); match(U,u,V,v);
  // If you want max independent set, put a ! around both if-statements
  for(int i=0;i<u;i++) if(U[i].pred == -1 && U[i].mate != -1) coverU.push_back(i);
  for(int i=0;i<v;i++) if(V[i].pred != -1) coverV.push_back(i);
  return coverU.size() + coverV.size();
}

typedef pair<string,string> pss;

void solve()
{
  int c, d, v;
  cin >> c >> d >> v;

  Node U[500], V[500];
  vector<pss> cats, dogs;

  
  for (int i = 0; i < v; i++) {
    string v1, v2;
    cin >> v1 >> v2;
    if (v1[0] == 'C') {
      cats.emplace_back(v1, v2);
    } else {
      dogs.emplace_back(v1, v2);
    }
  }

  for (int i = 0; i < cats.size(); i++) {
    for (int j = 0; j < dogs.size(); j++) {
      if (cats[i].first == dogs[j].second ||
	  cats[i].second == dogs[j].first) {
	add_edge(U, i, V, j);
      }
    }
  }

  cout << v - match(U, cats.size(), V, dogs.size()) << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();

  return 0;
}
