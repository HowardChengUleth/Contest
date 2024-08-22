#include <bits/stdc++.h>

using namespace std;

string ans[9];

int main()
{
  ans[0] = "{}";
  for (int n = 1; n <= 8; n++) {
    ans[n] = "{";
    for (int i = 0; i < n; i++) {
      if (i) {
	ans[n] += ",";
      }
      ans[n] += ans[i];
    }
    ans[n] += "}";
  }

  int n;
  cin >> n;
  cout << ans[n] << endl;
  

  return 0;
}
