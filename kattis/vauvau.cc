#include <bits/stdc++.h>

using namespace std;

bool attack(int agg, int calm, int t)
{
  // make things easier with 0 based
  t--;

  t %= (agg + calm);
  return t < agg;
}

int main()
{
  int A, B, C, D;
  cin >> A >> B >> C >> D;

  const string ans[] = { "none", "one", "both" };
  
  int t;
  for (int i = 0; i < 3; i++) {
    cin >> t;
    int dog = 0;
    if (attack(A, B, t)) {
      dog++;
    }
    if (attack(C, D, t)) {
      dog++;
    }
    cout << ans[dog] << endl;
  }


  return 0;
}
