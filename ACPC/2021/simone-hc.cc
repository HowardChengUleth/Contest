#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, K;
  cin >> N >> K;

  int freq[1001] = {0};
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    freq[x]++;
  }

  int least = *min_element(freq+1, freq+K+1);
  int times = count(freq+1, freq+K+1, least);
  cout << times << endl;
  for (int i = 1; i <= K; i++) {
    if (freq[i] == least) {
      cout << i << endl;
    }
  }
     
  return 0;
}
