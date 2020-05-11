#include <iostream>

using namespace std;

void solve(void)
{
  int n, P, Q;
  cin >> n >> P >> Q;

  int w[30];
  for (int i = 0; i < n; i++) {
    cin >> w[i];
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (P > 0 && Q >= w[i]) {
      P--;
      Q -= w[i];
      ans++;
    }
  }

  cout << ans << endl;
    
}

int main(void)
{
  int num;
  cin >> num;
  for (int i = 1; i <= num; i++) {
    cout << "Case " << i << ": ";
    solve();
  }

  return 0;
}
