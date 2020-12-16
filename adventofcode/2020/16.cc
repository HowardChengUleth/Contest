#include <bits/stdc++.h>

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




typedef pair<int,int> pii;

struct Field
{
  string name;
  pii range[2];

  Field(string line) {
    auto ind = line.find(':');
    name = line.substr(0, ind);
    line = line.substr(ind+1);
    for (auto &c : line) {
      if (!isdigit(c))
	c = ' ';
    }
    istringstream iss(line);

    for (int i = 0; i < 2; i++) {
      iss >> range[i].first >> range[i].second;
    }
  }

  bool valid(int x) const
  {
    return (range[0].first <= x && x <= range[0].second) ||
      (range[1].first <= x && x <= range[1].second);
  }
};

vector<Field> fields;

typedef vector<int> vi;
typedef vector<vi> vvi;

vi mine;
vvi others;

vector<bool> valid;

void read(vi &ticket, string line)
{
  for (auto &c : line) {
    if (c == ',') {
      c = ' ';
    }
  }
  istringstream iss(line);
  int x;

  ticket.clear();
  while (iss >> x) {
    ticket.push_back(x);
  }
}

void partA()
{
  int ans = 0;
  valid.resize(others.size());

  for (int i = 0; i < (int)others.size(); i++) {
    const auto &ticket = others[i];
    valid[i] = true;
    for (auto x : ticket) {
      bool found = false;
      for (auto f : fields) {
	if (f.valid(x)) {
	  found = true;
	  break;
	}
      }
      if (!found) {
	ans += x;
	valid[i] = false;
      }
    }
  }

  cout << "A = " << ans << endl;
}

bool can_match(int fi, int tj)
{
  if (!fields[fi].valid(mine[tj]))
    return false;
  for (int i = 0; i < others.size(); i++) {
    if (!valid[i]) continue;
    if (!fields[fi].valid(others[i][tj]))
      return false;
  }

  return true;
}

void partB()
{
  Node U[100], V[100];

  for (int i = 0; i < (int)fields.size(); i++) {
    for (int j = 0; j < (int)mine.size(); j++) {
      if (can_match(i, j)) {
	add_edge(U, i, V, j);
      }
    }
  }

  assert(fields.size() == mine.size());
  int M = match(U, fields.size(), V, mine.size());
  assert(M == fields.size());

  long long ans = 1;
  for (int i = 0; i < (int)fields.size(); i++) {
    if (fields[i].name.find("departure") != string::npos) {
      int id = U[i].mate;
      ans *= mine[id];
    }
  }

  cout << "B = " << ans << endl;
}

int main()
{
  string line;

  // read rules
  while (getline(cin, line) && line != "") {
    fields.emplace_back(line);
  }

  // read my ticket
  getline(cin, line);
  getline(cin, line);
  read(mine, line);
  getline(cin, line);

  // read other tickets
  getline(cin, line);
  while (getline(cin, line)) {
    vi ticket;
    read(ticket, line);
    others.push_back(ticket);
  }

  partA();
  partB();
  
  return 0;
}

