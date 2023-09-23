#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

int main()
{
  ull N, b;
  cin >> N >> b;

  ull m = (1ULL << (b+1)) - 1;
  cout << (N <= m ? "yes" : "no") << endl;
  
  return 0;
}
