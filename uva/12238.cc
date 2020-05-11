#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <cstdio>

using namespace std;

typedef long long ll;

struct Edge
{
  int v;
  ll len;
};

struct Graph {
  vector<vector<Edge> > nbr;
  int num_nodes;
  Graph(int n) : nbr(n), num_nodes(n) {
  }

  void add_edge(int u, int v, ll weight) {
    Edge e1 = {v,weight};   nbr[u].push_back(e1);
    Edge e2 = {u,weight};   nbr[v].push_back(e2);
  }
};

const int MAX_N = 2*100000;

typedef pair<int,int> Type;             // These two lines replace the
const Type oo = make_pair(INT_MAX,-1);  // corresponding  lines in rmq.cc

typedef pair<Type,int> pti;
const pti p_oo = make_pair(oo,-1);
int size;

void constructRMQ(Type A[MAX_N], pti M[4*MAX_N], int n) {
  size = 1; while(size < n) size <<= 1;
  for (int i=0; i < size; i++) M[size-1+i] = (i < n ? make_pair(A[i],i) : p_oo);
  for (int i=size-2; i>=0; i--) M[i] = min(M[2*i+1],M[2*i+2]);
}

pti getmin(pti M[4*MAX_N], int a, int b, int st=0,int en=size,int ind=0) {
  if (a > b || a >= en || b < st)         return p_oo;
  if ((a <= st && en <= b) || st+1 >= en) return M[ind];
  int mid = (st+en)/2;
  return min(getmin(M,a,b,st,mid,2*ind+1), getmin(M,a,b,mid,en,2*ind+2));
}

void update(Type A[MAX_N], pti M[4*MAX_N], int i, Type val){
  A[i] = val; M[i += size-1] = make_pair(val,i);
  while((i = (i-1)/2)) M[i] = min(M[2*i+1],M[2*i+2]);
}

void preLCA(const Graph& G,int r,int p,Type A[MAX_N],int loc[MAX_N],int d,int& idx){
  for(int i=0;i<G.nbr[r].size();i++){ int w = G.nbr[r][i].v;
    if(w != p) { A[idx++] = make_pair(d,r); preLCA(G,w,r,A,loc,d+1,idx); } }
  loc[r] = idx; A[idx++] = make_pair(d,r);
}
void constructLCA(const Graph& G,int root,pti M[4*MAX_N],int loc[MAX_N]){
  Type A[MAX_N]; int idx=0; preLCA(G,root,-1,A,loc,0,idx);
  constructRMQ(A,M,idx);
}
int LCA(pti M[4*MAX_N],int loc[MAX_N],int u,int v){
  return getmin(M,min(loc[u],loc[v]),max(loc[u],loc[v])).first.second;
}

int N;
ll depth[MAX_N];

void DFS(const Graph &G, int root, ll d)
{
  depth[root] = d;
  for (const auto &e : G.nbr[root]) {
    if (depth[e.v] >= 0) continue;
    DFS(G, e.v, d+e.len);
  }
}

pti M[4*MAX_N];
int loc[MAX_N];

bool solve()
{
  scanf("%d", &N);
  if (!N) return false;

  Graph G(N);

  for (int i = 1; i < N; i++) {
    int A, L;
    scanf("%d %d", &A, &L);
    G.add_edge(i, A, L);
  }

  fill(depth, depth+N, -1);
  DFS(G, 0, 0);
  constructLCA(G, 0, M, loc);

  int Q;
  scanf("%d", &Q);
  for (int i = 0; i < Q; i++) {
    if (i) printf(" ");

    int S, T;
    scanf("%d %d", &S, &T);

    int anc = LCA(M, loc, S, T);
    printf("%lld", depth[S] + depth[T] - 2*depth[anc]);
  }
  printf("\n");
  
  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
