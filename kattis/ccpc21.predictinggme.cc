#include <bits/stdc++.h>

using namespace std;

int n, price[1000];

int ans[2][1000];

int f(int hold, int day)
{
  if (day >= n)
    return 0;
  if (ans[hold][day] >= 0) {
    return ans[hold][day];
  }

  if (day == n-1) {
    if (!hold) {
      return ans[hold][day] = 0;
    } else {
      return ans[hold][day] = price[day];
    }
  }

  // don't do anything
  int t = f(hold, day+1);

  if (!hold) {
    // try to buy
    t = max(t, f(1, day+1)-price[day]);
  } else {
    // try to sell
    t = max(t, f(0, day+2)+price[day]);
  }
  return ans[hold][day] = t;
}

int main()
{
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> price[i];
    ans[0][i] = ans[1][i] = -1;
  }
  
  cout << f(0, 0) << endl;
  
  return 0;
}
