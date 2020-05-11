#include <bits/stdc++.h>

using namespace std;

class FenwickTree{  // All entries must be >= 0 even after decrement
public:             // Every function is O(log n)
  FenwickTree(int n = 0) : N(n), iBM(1), tree(n) {
    while (iBM < N) iBM *= 2;
  }

  // inc/dec the entry at position idx
  void flipEntry(int idx, int color) {
    do tree[idx].flip(color); while(idx && (idx += (idx & (-idx))) < N);
  }
  
  // return the cumulative sum val[0] ^ val[1] ^ ... ^ val[idx]
  bitset<100> cumulativeSum(int idx) const {
    bitset<100> sum = tree[0];
    for( ; idx > 0 ; idx &= idx-1) sum ^= tree[idx];
    return sum;
  }
    
private:
  int N, iBM; vector<bitset<100>> tree;
};

int parent[300000];
int C[300000];
vector<int> G[300000];
vector<int> tour;
int visited[300000];
int si[300000];
int ei[300000];

void DFS(int v)
{
  visited[v] = true;
  si[v] = tour.size();
  tour.push_back(v);
  for (auto w : G[v]) {
    if (visited[w]) continue;
    DFS(w);
  }
  ei[v] = tour.size();
  tour.push_back(v);
}

int main()
{
  int N, Q;
  cin >> N >> Q;
  tour.reserve(2*N);
  
  FenwickTree fw(2*N);

  for (int i = 0; i < N; i++) {
    cin >> C[i];
    C[i]--;
  }

  parent[0] = -1;
  for (int i = 0; i < N-1; i++) {
    cin >> parent[i+1];
    parent[i+1]--;
    G[parent[i+1]].push_back(i+1);
  }

  DFS(0);

  for (int i = 0; i < N; i++) {
    fw.flipEntry(si[i], C[i]);
  }

  while (Q--) {
    int K, X;
    cin >> K >> X;
    X--;
    if (K == 0) {
      bitset<100> total = fw.cumulativeSum(ei[X]);
      if (si[X] > 0) {
	total ^= fw.cumulativeSum(si[X]-1);
      }
      cout << total.count() << endl;
    } else {
      //      cout << si[X] << "*" << endl;
      int old = C[X];
      fw.flipEntry(si[X], old);
      fw.flipEntry(si[X], K-1);
      C[X] = K-1;
    }

  }
  
  return 0;
}
