/* @JUDGE_ID: 1102NT 538 C++ "" */

#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

using namespace std;

int main(void)
{
  int n, t, amount;
  string s1, s2;
  int cases = 0;

  while (cin >> n >> t && (n || t)) {
    vector< pair<int, string> > v;

    for (int i = 0; i < n; i++) {
      cin >> s1;
      v.push_back(make_pair<int, string>(0, s1));
    }

    for (int i = 0; i < t; i++) {
      cin >> s1 >> s2 >> amount;
      for (int j = 0; j < n; j++) {
	if (v[j].second == s1) {
	  v[j].first += amount;
	} else if (v[j].second == s2) {
	  v[j].first -= amount;
	}
      }
    }
    sort(v.begin(), v.end());
    
    cout << "Case #" << ++cases << endl;
    for (int i = 0; i < n; i++) {
      if (i < n-1 && v[i].first < 0) {
	cout << v[i].second << " " << v[i+1].second << " " << -v[i].first 
	     << endl;
	v[i+1].first += v[i].first;
	v[i].first = 0;
      }
    }
    cout << endl;
  }
  return 0;
}
