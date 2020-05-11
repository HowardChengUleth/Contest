#include <iostream>
#include <map>

using namespace std;

int main(void)
{
  int n;
  
  while (cin >> n && n > 0) {
    long long total = 0;
    map<int,int> S;
    for (int i = 0; i < n; i++) {
      int m;
      cin >> m;
      for (int j = 0; j < m; j++) {
	int t;
	cin >> t;
	S[t]++;
      }
      int small = S.begin()->first;
      int big = S.rbegin()->first;
      total += big - small;

      if (!(--S[small])) {
	S.erase(small);
      }
      if (!(--S[big])) {
	S.erase(big);
      }
    }

    cout << total << endl;
  }
  return 0;
}
