#include <bits/stdc++.h>

using namespace std;

int main()
{
  int K;
  cin >> K;

  int bar = 1;
  while (bar < K) {
    bar *= 2;
  }

  cout << bar << ' ';

  int breaks = 0;
  if (K >= bar) {
    K -= bar;
  }
  while (K != 0) {
    bar /= 2;
    if (K >= bar) {
      K -= bar;
    }
    breaks++;
  }

  cout << breaks << endl;
  
  return 0;
}
