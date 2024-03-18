#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, H, C;
  cin >> N >> H >> C;

  int candles[100][1000];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < H; j++) {
      cin >> candles[i][j];
    }
    sort(candles[i], candles[i]+H);
  }

  int used = 0;
  int blown = 0;
  for (int j = 0; j < H; j++) {
    int A[100];
    for (int i = 0; i < N; i++) {
      A[i] = candles[i][j];
    }
    sort(A, A+N);
    for (int i = 0; i < N; i++) {
      if (used + A[i] <= C) {
	used += A[i];
	blown++;
      } else {
	goto done;
      }
    }
  }

 done:
  cout << blown << endl;
    

  return 0;
}
