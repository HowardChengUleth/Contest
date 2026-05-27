#include <bits/stdc++.h>

using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

typedef pair<int,int> pii;
typedef tree<pii, null_type, less<pii>, rb_tree_tag,
             tree_order_statistics_node_update> ost;

void solve()
{
  int N;
  cin >> N;

  int64_t sum = 0;

  ost tree;
  
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;

    tree.insert(make_pair(x, i));

    int size = i+1;
    int mid = size/2;
    if (size % 2 == 1) {
      // odd number
      sum += tree.find_by_order(mid)->first;
    } else {
      // even number
      sum += (tree.find_by_order(mid)->first +
	      tree.find_by_order(mid-1)->first)/2;
    }
  }
  cout << sum << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
