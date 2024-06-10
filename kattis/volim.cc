#include <bits/stdc++.h>

using namespace std;

int main()
{
  int K;
  cin >> K;
  K--;

  int N;
  cin >> N;

  int time = 0;
  for (int i = 0; i < N; i++) {
    int t;
    char resp;
    cin >> t >> resp;
    time += t;
    if (time >= 210) {
      cout << K+1 << endl;
      break;
    }
    if (resp == 'T') {
      K = (K+1) % 8;
    }
  }


  return 0;
}
