#include <bits/stdc++.h>

using namespace std;

// Graph layout
//  -- Each problem has its own Edge structure.
// If you see "typedef int Edge;" at the top of an algorithm, change
//    vector<vector<Edge> > nbr; --->  vector<vector<int> > nbr;

typedef int Edge;

struct Graph {
  vector<vector<Edge> > nbr;
  int num_nodes;
  Graph(int n) : nbr(n), num_nodes(n) { }
  
  void add_edge(int u, int v) {
    Edge e1 = v;   nbr[u].push_back(e1);
    Edge e2 = u;   nbr[v].push_back(e2);
  }
};

const int MAX_EMPLOY = 100000;
const int MAX_N = 2*MAX_EMPLOY;

// RMQ:
//   call constructRMQ to get data structure M                   O(n)
//   call getmax to get the maximum from [a..b] inclusive        O(log n)
//     returns a pair of the form (maximum value,index of maximum value)
//   call update to change a value in the array                  O(log n)
typedef pair<int,int> Type;             // These two lines replace the
const Type oo = make_pair(INT_MAX,-1);  // corresponding  lines in rmq.cc

typedef pair<Type,int> pti;
const pti p_oo = make_pair(oo,-1);
int Size;

void constructRMQ(Type A[MAX_N], pti M[4*MAX_N], int n) {
  Size = 1; while(Size < n) Size <<= 1;
  for (int i=0; i < Size; i++) M[Size-1+i] = (i < n ? make_pair(A[i],i) : p_oo);
  for (int i=Size-2; i>=0; i--) M[i] = min(M[2*i+1],M[2*i+2]);
}

pti getmin(pti M[4*MAX_N], int a, int b, int st=0,int en=Size,int ind=0) {
  if (a > b || a >= en || b < st)         return p_oo;
  if ((a <= st && en <= b) || st+1 >= en) return M[ind];
  int mid = (st+en)/2;
  return min(getmin(M,a,b,st,mid,2*ind+1), getmin(M,a,b,mid,en,2*ind+2));
}

void update(Type A[MAX_N], pti M[4*MAX_N], int i, Type val){
  A[i] = val; M[i += Size-1] = make_pair(val,i);
  while((i = (i-1)/2)) M[i] = min(M[2*i+1],M[2*i+2]);
}

// include RMQ code (Minimum) -- MAX_N must be 2*MAX_NODES
//   call constructLCA once before starting      O(n)
//   call LCA to find lca of vertex u and v      O(log n)
//typedef int Edge;

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

pti MM[4*MAX_N];
int loc[MAX_N];

int main()
{
  int N, M;
  cin >> N >> M;
  
  Graph G(N);
  for (int i = 1; i < N; i++) {
    int p;
    cin >> p;
    G.add_edge(p-1, i);
  }

  constructLCA(G, 0, MM, loc);

  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    if (LCA(MM, loc, a-1, b-1) == b-1) {
      cout << "No" << endl;
    } else {
      cout << "Yes" << endl;
    }
  }
  

  return 0;
}
