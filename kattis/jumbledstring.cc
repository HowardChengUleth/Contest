#include <bits/stdc++.h>

using namespace std;

int solve(int a)
{
  for (long long N = 0; N*(N-1)/2 <= a; N++) {
    if (N*(N-1)/2 == a) {
      return N;
    }
  }
					       
  return -1;
}

int main()
{
  int a, b, c, d;
  cin >> a >> b >> c >> d;

  int N0 = solve(a);
  int N1 = solve(d);
  if (N0 < 0 || N1 < 0) {
    cout << "impossible" << endl;
    return 0;
  }

  if (N0 == 0) {
    // can be either 0 or 1
    if (b > 0 || c > 0) {
      N0 = 1;
    }
  }
  if (N1 == 0) {
    // can be either 0 or 1
    if (b > 0 || c > 0) {
      N1 = 1;
    }
  }
  if (N0 + N1 == 0) {
    // must be the case that b, c == 0
    N0 = 1;
  }
  string s;

  while (N0 + N1 > 0) {
    if (N0 > 0 && b >= N1) {
      s += '0';
      N0--;
      b -= N1;
    } else if (N1 > 0 && c >= N0) {
      s += '1';
      N1--;
      c -= N0;
    } else {
      cout << "impossible" << endl;
      return 0;
    }
  }
  if (b || c) {
    cout << "impossible" << endl;
  } else {
    cout << s << endl;
  }

  return 0;
}
