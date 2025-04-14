#include <bits/stdc++.h>

using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;
typedef tree<string, null_type, less<string>, rb_tree_tag,
	     tree_order_statistics_node_update> ost;

int main()
{
  // need fast I/O to get AC
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  ost tree[3];

  int cmd;
  while (cin >> cmd && cmd) {
    switch (cmd) {
    case 1:
      {
	string name;
	int gender;
	cin >> name >> gender;
	tree[gender].insert(name);
      }
      break;
    case 2:
      {
	string name;
	cin >> name;

	for (int g = 1; g <= 2; g++) {
	  tree[g].erase(name);
	}
      }
      break;
    case 3:
      {
	string sname, ename;
	int gender;
	cin >> sname >> ename >> gender;
	int ans = 0;
	for (int g = 1; g <= 2; g++) {
	  if (gender == 0 || gender == g) {
	    ans += tree[g].order_of_key(ename) - tree[g].order_of_key(sname);
	  }
	}
	cout << ans << '\n';
      }
    }

  }

  return 0;
}
