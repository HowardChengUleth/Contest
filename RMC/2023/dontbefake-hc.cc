#include <bits/stdc++.h>

using namespace std;

const int MAX_TIME = 86400;

int main()
{
  int N;
  cin >> N;

  int freq[MAX_TIME] = {0};
  for (int i = 0; i < N; i++) {
    int M;
    cin >> M;
    for (int j = 0; j < M; j++) {
      int L, R;
      cin >> L >> R;
      for (int k = L; k <= R; k++) {
	freq[k]++;
      }
    }
  }

  int pics = *max_element(freq, freq+MAX_TIME);
  int secs = count(freq, freq+MAX_TIME, pics);

  cout << pics << endl;
  cout << secs << endl;
  
  return 0;
}
