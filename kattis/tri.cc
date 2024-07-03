#include <bits/stdc++.h>

using namespace std;

// a op b = c
bool check(int a, int b, int c, int op)
{
  switch (op) {
  case 0:
    return a + b == c;
  case 1:
    return a - b == c;
  case 2:
    return a * b == c;
  case 3:
    return b * c == a;
  }
  return false;
}

int main()
{
  int a, b, c;
  cin >> a >> b >> c;

  string op = "+-*/";
  
  for (int i = 0; i < 4; i++) {
    if (check(a, b, c, i)) {
      cout << a << op[i] << b << '=' << c << endl;
      return 0;
    }

    if (check(b, c, a, i)) {
      cout << a << '=' << b << op[i] << c << endl;
      return 0;
    }
  }

  
  
  return 0;
}
