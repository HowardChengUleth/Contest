#include <bits/stdc++.h>

using namespace std;

int a[100000];
unordered_set<int> tree[300000];

// [left,right]
void build(int root, int left, int right)
{
  if (left == right) {
    tree[root].insert(a[left]);
    return;
  }
  if (left > right) return;

  int mid = (left + right)/2;
  build(2*root+1, left, mid);
  build(2*root+2, mid+1, right);

  set_union(tree[2*root+1].begin(), tree[2*root+1].end(),
	    tree[2*root+2].begin(), tree[2*root+2].end(),
	    inserter(tree[root], tree[root].end()));
}

int answer(int root, int left, int right, int i, const unordered_set<int> &b)
{
  if (left > right) return 0;
  if (left == right) {
    return (b.count(a[left]) >= 1) ? 1 : 0;
  }

  if (includes(b.begin(), b.end(), tree[root].begin(), tree[root].end())) {
    return right - i + 1;
  }
  
  int mid = (left + right)/2;

  int part1;
  if (i <= mid) {
    part1 = answer(2*root+1, left, mid, i, b);
    if (mid - i + 1 == part1) {
      part1 += answer(2*root+2, mid+1, right, mid+1, b);
    }
  } else {
    part1 = answer(2*root+2, mid+1, right, i, b);
  }
  return part1;
}

int main()
{
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  
  build(0, 0, n-1);

  int q;
  cin >> q;
  while (q--) {
    int i, m;
    unordered_set<int> b;

    cin >> i >> m;
    while (m--) {
      int x;
      cin >> x;
      b.insert(x);
    }

    cout << answer(0, 0, n-1, i-1, b) << endl;
  }

  return 0;
}
