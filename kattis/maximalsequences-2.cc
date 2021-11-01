#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> a;

int chunk_size;
vector<set<int>> chunk;

int do_query()
{
  int i, m;
  cin >> i >> m;
  i--;
  
  set<int> B;
  for (int j = 0; j < m; j++) {
    int x;
    cin >> x;
    B.insert(x);
  }

  int ans = 0;

  for (; i < n && i % chunk_size != 0; i++) {
    if (B.count(a[i]) == 0) {
      return ans;
    }
    ans++;
  }
  
  int chunk_idx = i / chunk_size;
  for (int j = i / chunk_size;
       j < chunk.size()-1 &&
	 includes(begin(B), end(B), begin(chunk[j]), end(chunk[j])); j++) {
    ans += chunk_size;
    i += chunk_size;
  }

  for (; i < n; i++) {
    if (B.count(a[i]) == 0) {
      return ans;
    }
    ans++;
  }

  return ans;
}

int main()
{
  cin >> n;
  a.resize(n);
  for (auto &x : a) {
    cin >> x;
  }

  chunk_size = ceil(sqrt(n));
  chunk.resize((n + chunk_size-1)/chunk_size);

  for (int i = 0; i < n; i++) {
    chunk[i/chunk_size].insert(a[i]);
  }

  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    cout << do_query() << endl;
  }
  
  return 0;
}
