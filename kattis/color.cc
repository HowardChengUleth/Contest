#include <bits/stdc++.h>

using namespace std;

int main()
{
  int S, C, K;
  cin >> S >> C >> K;

  int D[100000];
  for (int i = 0; i < S; i++) {
    cin >> D[i];
  }
  sort(D, D+S);

  int ans = 0;
  int i, j;
  for (i = 0; i < S; i = j) {
    for (j = i; j < S && j-i < C && D[j] - D[i] <= K; j++)
      ;
    ans++;
  }

  cout << ans << endl;
  return 0;
}
