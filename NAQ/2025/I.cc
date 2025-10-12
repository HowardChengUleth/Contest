#include <bits/stdc++.h>

using namespace std;

typedef int64_t ll;

int n;
vector<ll> a, s;

double f(int index, ll total, int num)
{
  if (index >= n) {
    if (num > 0) {
      return (double(total) + a[num-1]) / num;
    } else {
      return -1;
    }
  }

  double ans1 = f(index+1, total, num);
  double ans2 = f(index+1, total + s[index], num+1);

  return max(ans1, ans2);
}

int main()
{
  cin >> n;
  
  for (int i = 0; i < n; i++) {
    ll x;
    cin >> x;
    a.push_back(x);
  }
  for (int i = 0; i < n; i++) {
    ll x;
    cin >> x;
    s.push_back(x);
  }

  double ans = f(0, 0, 0);

  cout << fixed << setprecision(10) << ans << endl;
  
  return 0;
}
