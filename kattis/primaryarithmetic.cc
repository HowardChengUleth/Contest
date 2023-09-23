#include <bits/stdc++.h>

using namespace std;

bool solve()
{
  string s1, s2;
  cin >> s1 >> s2;
  if (s1 == "0" && s2 == "0")
    return false;

  reverse(begin(s1), end(s1));
  reverse(begin(s2), end(s2));

  int num_carry = 0;
  int carry = 0;
  for (int i = 0; i < s1.length() || i < s2.length(); i++) {
    int d1 = (i < s1.length()) ? s1[i] - '0' : 0;
    int d2 = (i < s2.length()) ? s2[i] - '0' : 0;
    int sum = d1 + d2 + carry;
    num_carry += (carry = (sum >= 10));
  }

  if (num_carry == 0) {
    cout << "No ";
  } else {
    cout << num_carry << ' ';
  }
  cout << "carry operation";
  if (num_carry > 1) {
    cout << "s";
  }
  cout << "." << endl;
  
  return true;
}

int main()
{
  while (solve())
    ;

  return 0;
}
