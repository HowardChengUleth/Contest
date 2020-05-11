#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

ull ways[25][145];

void init()
{
  ways[0][0] = 1;
  for (int n = 1; n <= 24; n++) {
    for (int T = 0; T <= 144; T++) {
      for (int d = 1; d <= min(T,6); d++) {
	ways[n][T] += ways[n-1][T-d];
      }
    }
  }
}

int main()
{
  init();

  int K, T;
  cin >> K >> T;

  int sum = 0;
  int freq[7] = {0};
  for (int i = 0; i < K; i++) {
    int r;
    cin >> r;
    freq[r]++;
    sum += r;
  }

  ull max_ways[25] = {0};
  for (int i1 = 0; i1 <= freq[1]; i1++) {
      for (int i2 = 0; i2 <= freq[2]; i2++) {
	  for (int i3 = 0; i3 <= freq[3]; i3++) {
	      for (int i4 = 0; i4 <= freq[4]; i4++) {
		  for (int i5 = 0; i5 <= freq[5]; i5++) {
		      for (int i6 = 0; i6 <= freq[6]; i6++) {
			int S = i1 + i2*2 + i3*3 + i4*4 + i5*5 + i6*6;
			int n = i1 + i2 + i3 + i4 + i5 + i6;
			int newT = T - (sum - S);
			if (newT < 0) continue;
			max_ways[n] = max(max_ways[n], ways[n][newT]);
		      }
		  }
	      }
	  }
      }
  }

  ull best_num = max_ways[0];
  int best_n = 0;

  for (int i = 1; i <= K; i++) {
    best_num *= 6;
    if (max_ways[i] > best_num) {
      best_n = i;
      best_num = max_ways[i];
    }
  }
  cout << best_n << endl;
  
  
  return 0;
}
