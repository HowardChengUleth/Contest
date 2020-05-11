#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

int sasc_seq(int A[], int n, int endlen[])
{
  vector<int> last(n+1);
  if (n == 0) {
    return 0;
  }

  int len = 1;
  last[1] = A[0];
  endlen[0] = 1;
  
  for (int i = 1; i < n; i++) {
    int j = lower_bound(last.begin()+1, last.begin()+len+1, A[i]) -
      last.begin();
    last[j] = A[i];
    len = max(len, j);
    endlen[i] = j;
  }

  return len;
}

void solve(int A[], int Arev[], int n)
{
  int endlen[10000], endlenrev[10000];

  sasc_seq(A, n, endlen);
  sasc_seq(Arev, n, endlenrev);

  int best = 1;
  for (int i = 0; i < n; i++) {
    int temp = 2*min(endlen[i], endlenrev[n-1-i]) - 1;
    best = max(best, temp);
  }
  cout << best << endl;
}

int main(void)
{
  int N;
  int A[10000];
  int Arev[10000];

  while (cin >> N) {
    for (int i = 0; i < N; i++) {
      cin >> A[i];
      Arev[N-1-i] = A[i];
    }
    solve(A, Arev, N);
  }
  return 0;
}
