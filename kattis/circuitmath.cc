#include <bits/stdc++.h>

using namespace std;

bool val[256];

int main()
{
  int n;
  cin >> n;

  char c;
  for (int i = 0; i < n; i++) {
    cin >> c;
    val['A'+i] = (c == 'T');
  }

  stack<bool> S;
  while (cin >> c) {
    if (isupper(c)) {
      S.push(val[c]);
    } else if (c == '*') {
      bool x = S.top(); S.pop();
      bool y = S.top(); S.pop();
      S.push(x && y);
    } else if (c == '+') {
      bool x = S.top(); S.pop();
      bool y = S.top(); S.pop();
      S.push(x || y);
    } else {
      bool x = S.top(); S.pop();
      S.push(!x);
    }
  }

  cout << (S.top() ? "T" : "F") << endl;
  return 0;
}
