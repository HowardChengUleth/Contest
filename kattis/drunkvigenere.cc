#include <bits/stdc++.h>

using namespace std;

int main()
{
  string C, K;
  cin >> C >> K;

  for (int i = 0; i < C.length(); i++) {
    int c = C[i] - 'A';
    int k = K[i] - 'A';
    if (i % 2 == 0) {
      C[i] = (c - k + 26) % 26 + 'A';
    } else {
      C[i] = (c + k) % 26 + 'A';
    }
  }
  cout << C << endl;
  
  return 0;
}
	
