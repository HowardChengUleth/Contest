#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef long long ll;

// position of string in the code
ll gray_pos(string a)
{
  int n = a.length();
  if (n == 1) {
    return a == "0" ? 0 : 1;
  }

  if (a[0] == '0') {
    // first half
    return gray_pos(a.substr(1));
  } else {
    // second half
    return (1UL << n) - 1 - gray_pos(a.substr(1));
  }
}

ll gray_dist(string a, string b)
{
  assert(a != b);

  ll pa = gray_pos(a);
  ll pb = gray_pos(b);
  return pb - pa - 1;
}

int main()
{
  int n;
  string a, b;

  cin >> n >> a >> b;

  cout << gray_dist(a, b) << endl;
  
  return 0;
}
