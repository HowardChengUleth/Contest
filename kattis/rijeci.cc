#include <bits/stdc++.h>

using namespace std;

int main()
{
  int nA = 1, nB = 0;

  int K;
  cin >> K;
  for (int i = 0; i < K; i++) {
    int nA2 = nB;
    int nB2 = nB + nA;
    nA = nA2;
    nB = nB2;
  }

  cout << nA << ' ' << nB << endl;

  
  return 0;
}
