#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <utility>

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

int sasc_seq_rev(int A[], int n, int startlen[])
{
  vector<int> first(n+1);   // largest start of seq of length k
  if (n == 0) {
    return 0;
  }

  int len = 1;
  first[1] = A[n-1];
  startlen[n-1] = 1;
  for (int i = n-2; i >= 0; i--) {
    int j = lower_bound(first.begin()+1, first.begin()+len+1, A[i],
			greater<int>()) - first.begin();
    first[j] = A[i];
    len = max(len, j);
    startlen[i] = j;
  }
  return len;
}

void solve(int A[], int Arev[], int n)
{
  int startlen[2000], endlenrev[2000];

  sasc_seq_rev(A, n, startlen);
  sasc_seq(Arev, n, endlenrev);

  int best = 0;
  for (int i = 0; i < n; i++) {
    int temp = startlen[i] + endlenrev[n-1-i] - 1;
    best = max(best, temp);
  }
  cout << best << endl;
}

int main(void)
{
  int T, n;
  int A[2000];
  int Arev[2000];

  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> A[i];
      Arev[n-1-i] = A[i];
    }
    solve(A, Arev, n);
  }
  return 0;
}
