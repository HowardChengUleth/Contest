#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 100*1000;

void ks(int n, int val[], int sum[])
{
  fill(sum, sum+MAX+1, -1);
  sum[0] = 0;
  int total = 0;

  for (int i = 0; i < n; i++) {
    total += val[i];
    int start = min(total, MAX);
    for (int j = start; j - val[i] >= 0; j--) {
      if (sum[j-val[i]] < 0) continue;
      int newval = sum[j-val[i]]+1;
      if (sum[j] < 0 || newval < sum[j]) {
	sum[j] = newval;
      }
    }
  }
}

int main()
{
  int H, B;
  int h[100], b[100];

  cin >> H;
  for (int i = 0; i < H; i++) {
    cin >> h[i];
  }
  cin >> B;
  for (int i = 0; i < B; i++) {
    cin >> b[i];
  }

  int hsum[MAX+1], bsum[MAX+1];

  ks(H, h, hsum);

  ks(B, b, bsum);

  int best = (H+B)+1;
  for (int i = 1; i <= MAX; i++) {
    if (hsum[i] >= 0 && bsum[i] >= 0) {
      best = min(best, hsum[i]+bsum[i]);
    }
  }

  if (best > H+B) {
    cout << "impossible" << endl;
  } else {
    cout << best << endl;
  }
  return 0;
}
