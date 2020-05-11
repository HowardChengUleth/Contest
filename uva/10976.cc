#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
  int k;
  while (cin >> k) {
    vector<pair<int,int> > sols;
    long long x, y;
    for (x = k+1; ; x++) {
      if (x*k % (x-k) != 0) continue;
      y = x*k/(x-k);
      sols.push_back(make_pair(x,y));
      if (x == y) break;
    }
    for (int i = 0; i < sols.size(); i++) {
      if (sols[i].first < sols[i].second) {
	swap(sols[i].first, sols[i].second);
      }
    }
    sort(sols.begin(), sols.end());
    cout << sols.size() << endl;
    for (int i = sols.size()-1; i >= 0; i--) {
      cout << "1/" << k << " = 1/" << sols[i].first << " + 1/"
	   << sols[i].second << endl;
    }
  }
  return 0;
}
