#include <bits/stdc++.h>

using namespace std;

int eval(int a, int b, char op, bool &error)
{
  error = (op == '/' && b == 0);
  if (error) return -1;

  switch (op) {
  case '+':
    return a+b;
  case '-':
    return a-b;
  case '*':
    return a*b;
  case '/':
    return a/b;
  }

  error = true;
  return -1;
}

int main()
{
  const string op = "*+-/";
  int a, b, c, d;
  bool error1, error2;
  int count = 0;
  
  cin >> a >> b >> c >> d;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (eval(a, b, op[i], error1) == eval(c, d, op[j], error2)) {
	if (!error1 && !error2) {
	  cout << a << ' ' << op[i] << ' ' << b << " = "
	       << c << ' ' << op[j] << ' ' << d << endl;
	  count++;
	}
      }
    }
  }

  if (!count) {
    cout << "problems ahead" << endl;
  }
  
  return 0;
}
