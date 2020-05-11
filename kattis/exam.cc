#include <bits/stdc++.h>

using namespace std;

// if x is the number of correct answers in the same part, then
//
// x <= same
// x <= k
// k-x + same <= x
//
// number of correct answers are x + (n - same - k + x)

int main()
{
  int k;
  cin >> k;

  string s1, s2;
  cin >> s1 >> s2;

  int n = s1.length();
  int same = 0;
  for (int i = 0; i < n; i++) {
    same += s1[i] == s2[i];
  }

  cout << 2*min(k,same) + n - same - k << endl;
  
  return 0;
}
