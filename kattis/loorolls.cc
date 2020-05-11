#include <bits/stdc++.h>

using namespace std;

int main()
{
  long long n, l;
  long long k = 1;
  cin >> l >> n;
  while (l % n > 0) {
    k++;
    n = n - l % n;
  }
  cout << k << endl;
  return 0;
}
