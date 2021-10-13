#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  int n;
  cin >> n;

  ll prev = 1;
  for (int i = 0; i < n; i++) {
    ll a, b, ans;
    char op;
    cin >> a >> op >> b;
    switch (op) {
    case '+':
      ans = a + b - prev;
      break;
    case '-':
      ans = (a - b) * prev;
      break;
    case '*':
      ans = a * b * a * b;
      break;
    case '/':
      ans = (a+1)/2;
      break;
    }
    cout << ans << endl;
    prev = ans;
  }
  return 0;
}
