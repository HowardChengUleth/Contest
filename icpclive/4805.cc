#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

const int MAX_N = 2*100001;

typedef pair<int,int> Type;             // These two lines replace the
const Type oo = make_pair(INT_MAX,-1);  // corresponding  lines in rmq.cc
typedef int Edge;

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

struct Graph {
  vector<vector<Edge> > nbr;
  int num_nodes;
  Graph(int n) : nbr(n), num_nodes(n) { }
  
  void add_edge(int u, int v) {
    Edge e1 = v;   nbr[u].push_back(e1);
    Edge e2 = u;   nbr[v].push_back(e2);
  }
};

void preLCA(const Graph& G,int r,int p,Type A[MAX_N],int loc[MAX_N],int d,int& idx){
  for(int i=0;i<G.nbr[r].size();i++){ int w = G.nbr[r][i];
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



typedef long long ll;

ll d[MAX_N];
int loc[MAX_N];
pti M[4*MAX_N];

bool solve()
{
  int N;
  cin >> N;
  if (!N) return false;

  Graph G(N);

  d[0] = 0;
  for (int i = 1; i < N; i++) {
    int A, L;
    cin >> A >> L;
    d[i] = d[A] + L;
    G.add_edge(A, i);
  }

  constructLCA(G, 0, M, loc);

  int Q;
  cin >> Q;
  while (Q--) {
    int S, T;
    cin >> S >> T;

    int anc = LCA(M, loc, S, T);
    cout << d[S] + d[T] - 2*d[anc];
    if (Q) cout << ' ';
  }
  
  cout << endl;
  return true;
}



int main()
{
  while (solve())
    ;
  
  return 0;
}
