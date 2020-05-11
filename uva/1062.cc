#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

string X;
int n;

int lis() {
  vector<int> last(n+1);
  if (n == 0) return 0;
  int len = 1; last[1] = X[0];
  for (int i = 1; i < n; ++i) {
    int j = lower_bound(last.begin()+1, last.begin()+len+1, X[i]) -
      last.begin();
    last[j] = X[i];
    len = max(len, j);
  }
  return len;
}

int main() {
  int cc = 1;
  while (cin >> X && X != "end") {
    n = X.size();
    int ans = 0;
    ans = lis();
    cout << "Case " << cc++ << ": " << ans << endl;
  }
  return 0;
}
