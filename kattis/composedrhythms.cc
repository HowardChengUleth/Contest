#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  int K = N/2;
  cout << K << endl;
  if (N % 2) {
    cout << 3 << ' ';
    K--;
  }
  for (int i = 0; i < K; i++) {
    cout << 2 << ' ';
  }
  cout << endl;
  
  
  return 0;
}
