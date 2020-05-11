#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

bool solve()
{
  int n;
  cin >> n;
  if (!n) return false;

  int best = 0;
  typedef map<vector<int>, int> Map;
  typedef Map::iterator MapIt;
  
  Map M;
  for (int i = 0; i < n; i++) {
    vector<int> v(5);
    for (int j = 0; j < 5; j++) {
      cin >> v[j];
    }
    sort(v.begin(), v.end());
    best = max(best, ++M[v]);
  }

  int ans = 0;
  for (MapIt it = M.begin(); it != M.end(); ++it) {
    if (it->second == best) {
      ans += best;
    }
  }
  
  cout << ans << endl;
  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
