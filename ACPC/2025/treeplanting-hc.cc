#include <bits/stdc++.h>

using namespace std;

const int MOD = 1'000'000'007;

int query_ans[100000];

// year->index
multimap<int,int> query;


int main()
{
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int y;
    cin >> y;
    query.insert(make_pair(y, i));
  }

  // tree[i] = number of trees i years old
  int tree[4] = {1, 0, 0, 0};

  for (int y = 0; y <= 10'000'001; y++) {
    auto [b, e] = query.equal_range(y);
    for (auto it = b; it != e; ++it) {
      query_ans[it->second] = (tree[1] + tree[2]) % MOD;
    }

    int tree2[4] = {0};
    tree2[3] = (tree[3] + tree[2]) % MOD;
    tree2[2] = tree[1];
    tree2[1] = tree[0];
    tree2[0] = (tree2[3] + 1) % MOD;

    copy(tree2, tree2+4, tree);
  }

  for (int i = 0; i < n; i++) {
    cout << query_ans[i] << endl;
  }

  return 0;
}
