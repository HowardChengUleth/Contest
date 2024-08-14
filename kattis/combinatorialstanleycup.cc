#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  cout << (1ULL << __builtin_popcount(N)) << endl;

  return 0;
}
