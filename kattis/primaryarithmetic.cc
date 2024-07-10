#include <bits/stdc++.h>

using namespace std;

void solve(const string &s1, const string &s2)
{
  int A1[11] = {0}, A2[11] = {0};

  int len1 = 0, len2 = 0;
  for (auto c : s1) {
    A1[len1++] = c - '0';
  }
  for (auto c : s2) {
    A2[len2++] = c - '0';
  }
  reverse(A1, A1+len1);
  reverse(A2, A2+len2);

  int ans = 0;
  int carry = 0;
  for (int i = 0; i < 10; i++) {
    int sum = A1[i] + A2[i] + carry;
    if (carry = (sum >= 10)) {
      ans++;
    }
  }

  if (ans == 0) {
    cout << "No carry operation." << endl;
  } else if (ans == 1) {
    cout << "1 carry operation." << endl;
  } else {
    cout << ans << " carry operations." << endl;
  }
}

int main()
{
  string s1, s2;
  while (cin >> s1 >> s2 && !(s1 == "0" && s2 == "0")) {
    solve(s1, s2);
  }

  return 0;
}
