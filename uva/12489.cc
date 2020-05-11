#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

const int MAX_N = 10030;
int A[MAX_N][MAX_N],deg[MAX_N];

struct Tuple{
   vector<int> v;
   bool operator<(const Tuple& x) const{
      if(v.size() != x.v.size()) // Size first
	 return v.size() < x.v.size();
      return v < x.v; // Then lexicographically
   }
};

map<Tuple,int> M;

int parent[MAX_N],max_lvl,deepest;
void dfs(int lvl,int v,int p){
   parent[v] = p;
   if(lvl > max_lvl){ max_lvl = lvl; deepest = v; }
   
   for(int i=0;i<deg[v];i++)
      if(A[v][i] != p)
	 dfs(lvl+1,A[v][i],v);
}

void centre(int& c1,int& c2){
   max_lvl = -1;
   dfs(0,1,-1);

   max_lvl = -1;
   dfs(0,deepest,-1);
   
   for(int i=0;i<max_lvl/2;i++)
      deepest = parent[deepest];
   c1 = deepest;
   c2 = (max_lvl % 2 == 0 ? c1 : parent[c1]);
}

int tot = 1;

int signature(int v,int p=-1){
   if(p != -1 && deg[v] == 1) // Leaf
      return 0;
   
   Tuple tmp;
   for(int i=0;i<deg[v];i++)
      if(A[v][i] != p)
	 tmp.v.push_back(signature(A[v][i],v));
   sort(tmp.v.begin(),tmp.v.end());
   if(M.find(tmp) == M.end())
      M[tmp] = tot++;
   
   return M[tmp];
}

void getSignatures(int N,int& sig1,int& sig2){
   fill(deg,deg+N+1,0);

   int u,v;
   for(int i=0;i<N-1;i++){
      cin >> u >> v;
      A[u][deg[u]++] = v;
      A[v][deg[v]++] = u;
   }

   int c1,c2;
   centre(c1,c2);

   sig1 = signature(c1);
   sig2 = (c1 != c2 ? signature(c2) : sig1);
}

bool do_case(int N){
   M.clear(); // Speeds it up 0.352 seconds vs 0.416 seconds
   int sigA1,sigA2,sigB1,sigB2;
   getSignatures(N,sigA1,sigA2);
   getSignatures(N,sigB1,sigB2);
   
   return (sigA1 == sigB1) || (sigA1 == sigB2) ||
      (sigA2 == sigB1) || (sigA2 == sigB2);   
}

int main(){
   int N;
   while(cin >> N)
      cout << (do_case(N) ? 'S' : 'N') << endl;
   return 0;
}
