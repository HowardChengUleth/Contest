//
// DP with table ans[n][f] = min dizziness to achieve total fun after n
// segments, or -1 if not possible.

#include <iostream>
#include <algorithm>

using namespace std;

bool do_case()
{
  int N, K, L;
  cin >> N >> K >> L;
  if (!N && !K && !L) return false;

  int F[1000], D[1000];
  for (int i = 0; i < N; i++) {
    cin >> F[i] >> D[i];
  }

  int ans[2][20*1000+1];    // we only need two rows
  fill(ans[0], ans[0]+20*N+1, -1);
  fill(ans[1], ans[1]+20*N+1, -1);
  ans[1][0] = 0;
  int curr = 0;
  int prev = 1;
  int maxfun = 0;

  for (int i = 0; i < N; i++) {
    fill(ans[curr], ans[curr]+maxfun+F[i]+1, -1);
    int currmax = 0;
    for (int f = 0; f <= maxfun; f++) {
      if (ans[prev][f] < 0) continue;

      // try closing eyes
      int reduceto = max(0, ans[prev][f] - K);
      if (ans[curr][f] < 0 || reduceto < ans[curr][f]) {
	ans[curr][f] = reduceto;
      }

      // try keeping eyes open
      int dizzy = ans[prev][f] + D[i];
      if (dizzy > L) continue;
      int fun = f + F[i];
      if (ans[curr][fun] < 0 || dizzy < ans[curr][fun]) {
	ans[curr][fun] = dizzy;
      }
      currmax = fun;
    }

    maxfun = max(currmax, maxfun);
    curr = 1-curr;
    prev = 1-prev;
  }

  cout << maxfun << endl;
  
  return true;
}
 
int main(void)
{
  while (do_case())
    ;

  return 0;
}
