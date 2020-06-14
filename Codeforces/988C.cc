#include <bits/stdc++.h>

using namespace std;

// For each list, we can get the total and subtract each element from
// the total to see what sum we can obtain from that list.  If we
// store the possible sums in a map, we can look for collisions and those
// are the answers.  Only thing to worry about is to make sure we don't get
// a collision between two sums in the same list.


int main()
{
  int k;
  cin >> k;
  
  vector<vector<int>> v(k);
  for (int i = 0; i < k; i++) {
    int n;
    cin >> n;
    v[i].reserve(n);
    while (n--) {
      int a;
      cin >> a;
      v[i].push_back(a);
    }
  }

  map<int, pair<int,int>> sums;
  
  for (int i = 0; i < k; i++) {
    int total = accumulate(begin(v[i]), end(v[i]), 0);
    for (int j = 0; j < v[i].size(); j++) {
      int s = total - v[i][j];
      if (sums.find(s) != sums.end()) {
	auto p = sums[s];
	if (p.first != i) {
	  cout << "YES" << endl;
	  cout << p.first+1 << ' ' << p.second+1 << endl;
	  cout << i+1 << ' ' << j+1 << endl;
	  return 0;
	}
      } else {
	sums[s] = make_pair(i, j);
      }
    }
  }
  cout << "NO" << endl;
  
  return 0;
}
