#include <bits/stdc++.h>

using namespace std;

int main()
{
  int C, N, M;
  cin >> C >> N >> M;

  long long freq[1001] = {0};
  for (int i = 0; i < N; i++) {
    int c;
    cin >> c;
    freq[c]++;
  }

  long long num_farms[51];
  num_farms[0] = accumulate(freq, freq+C+1, 0LL);

  for (int dd = 1; dd <= 50; dd++) {
    long long freq2[1001] = {0};
    for (int i = 0; i <= C; i++) {
      int j = i*2;
      long long num = freq[i];
      if (j <= C) {
	freq2[j] += num;
      } else {
	int j1 = j/2;
	int j2 = j - j1;
	freq2[j1] += num;
	freq2[j2] += num;
      }
    }
    copy(freq2, freq2+C+1, freq);
    num_farms[dd] = accumulate(freq, freq+C+1, 0LL);
  }

  for (int i = 0; i < M; i++) {
    int d;
    cin >> d;
    cout << num_farms[d] << endl;
  }



}
