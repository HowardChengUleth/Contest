#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

int main(void)
{
  int cases;
  cin >> cases;
  while (cases-- > 0) {
    int n;
    cin >> n;
    int p[20000];

    for (int i = 0; i < n; i++) {
      cin >> p[i];
    }
    sort(p, p+n, greater<int>());

    int ans = 0;
    for (int i = 2; i < n; i += 3) {
      ans += p[i];
    }

    cout << ans << endl;


  }
  return 0;
}
