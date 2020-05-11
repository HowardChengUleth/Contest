#include <iostream>
#include <algorithm>

using namespace std;

void solve()
{
  int N;
  cin >> N;

  int L[100001];
  int sum = 0;
  for (int i = 1; i <= N; i++) {
    cin >> L[i];
    sum += L[i];
  }

  int partfwd[100001], partbwd[100002];
  partfwd[1] = 0;
  for (int i = 2; i <= N; i++) {
    partfwd[i] = partfwd[i-1] + L[i-1];
  }
  partbwd[N+1] = 0;
  for (int i = N; i >= 2; i--) {
    partbwd[i] = partbwd[i+1] + L[i];
  }

  int best = 1000000000;
  
  // try exit i, never want to exit at room 1
  for (int i = 2; i <= N; i++) {
    // go to room i-1, double back to room 1, and then to room i
    int t1 = 2*partfwd[i-1] + partbwd[i];
    
    // go to room i+1, double back to room 1, and then to room i
    int t2 = 2*partbwd[i+1] + partfwd[i];

    best = min(best, min(t1, t2));
  }
  cout << best << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
