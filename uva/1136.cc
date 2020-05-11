#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>


using namespace std;

struct RMQ
{
  vector<int> A;
  int offset;
  int N;

  RMQ(int n, int K)
    : A(3*n), offset(0), N(n)
  {
    int size = 1;

    while (size < N) {
      offset += size;
      size *= 2;
    }

    fill(A.begin(), A.end(), K);
  }

  int value(int node) const
  {
    return A[node + offset];
  }

  int min_index(int v) const
  {
    int node = 0;
    
    while (node < offset) {
      int left = 2*node+1, right = 2*node+2;
      node = (A[left] >= v) ? left : right;
    }

    return node - offset;
  }

  void update(int node, int v)
  {
    node += offset;
    A[node] = v;
    while (node > 0) {
      int parent = (node-1)/2;
      int left = 2*parent+1, right = 2*parent+2;
      A[parent] = max(A[left], A[right]);
      node = parent;
    }
  }
};

int K, n;
int c[1000000];

bool read_case()
{
  if (!(cin >> K >> n)) return false;

  int ci = 0;
  while (ci < n) {
    char b;
    int r, v;
    if (cin >> v) {
      c[ci++] = v;
    } else {
      cin.clear();
      cin >> b >> r >> v;
      while (r--) {
	c[ci++] = v;
      }
    }
  }
  
  return true;
}

void solve()
{
  RMQ rmq(n, K);

  for (int i = 0; i < n; i++) {
    int index = rmq.min_index(c[i]);
    rmq.update(index, rmq.value(index) - c[i]);
  }

  int s = 0, w = 0;
  for (int i = 0; i < n; i++) {
    if (rmq.value(i) < K) {
      w += rmq.value(i);
      s++;
    }
  }
  cout << s << ' ' << w << endl;
}

int main()
{
  bool first = true;
  while (read_case()) {
    if (!first) cout << endl;
    solve();
    first = false;
  }

  return 0;
}
	
