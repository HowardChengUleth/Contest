#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const string digits = "0123456789abcdefghijklmnopqrstuvwxyz";
const string base_out = "*123456789abcdefghijklmnopqrstuvwxyz0";
const ll max_int = (1ULL << 32) - 1;

int value(char c, int b)
{
  if (b == 1) {
    return (c == '1') ? 1 : -1;
  }
  string::size_type pos = digits.find(c);
  return (pos != string::npos && pos < b) ? pos : -1;
}
          
ll value(string s, int b)
{
  ll val = 0;
  for (int i = 0; i < s.length(); i++) {
    int t = value(s[i], b);
    if (t < 0) return -1;
    val = val*b + t;
    if (val > max_int) return -1;
  }
  return val;
}

void solve()
{
  string X, Y, Z;
  char op, eq;
  cin >> X >> op >> Y >> eq >> Z;

  bool found = false;
  for (int b = 1; b <= 36; b++) {
    ll xval = value(X, b);
    ll yval = value(Y, b);
    ll zval = value(Z, b);
    if (xval < 0 || yval < 0 || zval < 0) continue;
    ll result;
    switch (op) {
    case '+':
      result = xval + yval;
      break;
    case '-':
      result = xval - yval;
      break;
    case '*':
      result = xval * yval;
      break;
    case '/':
      if (yval == 0 || xval % yval != 0) {
        result = -1;
      } else {
        result = xval / yval;
      }
    }
    if (result == zval) {
      cout << base_out[b];
      found = true;
    }
  }
  if (!found) {
    cout << "invalid";
  }
  cout << endl;
}

int main()
{
  int N;
  cin >> N;
  while (N--)
    solve();
  
  return 0;
}

