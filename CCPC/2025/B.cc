#include <bits/stdc++.h>

using namespace std;

int T, L, C, W;
bool A[1000];
int csum[1000];

// best[pos][claws]
int best[1001][1001];

int f(int pos, int num_claws)
{
  if (pos + W - 1 >= L) {
    return 0;
  }
  if (num_claws == 0) {
    return 0;
  }
  if (best[pos][num_claws] >= 0) {
    return best[pos][num_claws];
  }


  int ans1 = f(pos+1, num_claws);

  int sum_start = (pos == 0) ? 0 : csum[pos-1];
  int sum_end = csum[pos+W-1];
  int ans2 = f(pos+W, num_claws-1) + sum_end - sum_start;

  return best[pos][num_claws] = max(ans1, ans2);
}

int main()
{
  cin >> T >> L >> C >> W;
  for (int i = 0; i < T; i++) {
    int x;
    cin >> x;
    A[x-1] = true;
  }

  csum[0] = A[0] ? 1 : 0;
  for (int i = 1; i < L; i++) {
    csum[i] = csum[i-1] + (A[i] ? 1 : 0);
  }
  for (int i = 0; i <= 1000; i++) {
    fill(best[i], best[i]+1001, -1);
  }

  cout << f(0, C) << endl;

  return 0;
}
