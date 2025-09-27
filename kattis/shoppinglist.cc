#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n, m;
  cin >> n >> m;

  set<string> result;
  for (int i = 0; i < n; i++) {
    set<string> curr_list;
    for (int j = 0; j < m; j++) {
      string s;
      cin >> s;
      curr_list.insert(s);
    }

    if (i == 0) {
      result = curr_list;
    } else {
      set<string> old = result;
      result.clear();
      set_intersection(begin(old), end(old),
		       begin(curr_list), end(curr_list),
		       inserter(result, begin(result)));
    }
  }

  cout << result.size() << endl;
  for (auto s : result) {
    cout << s << endl;
  }


  return 0;
}
