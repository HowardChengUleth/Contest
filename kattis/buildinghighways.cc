#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;
  
  vector<int64_t> A(N);
  for (auto &x : A) {
    cin >> x;
  }
  sort(begin(A), end(A));

  // basically, we always want to connect A[i] - A[0] for all i > 0, because
  // there is no smaller way to connect A[i] to the tree

  int64_t cost = (N-1) * A[0] + accumulate(begin(A)+1, end(A), int64_t(0));
  
  cout << cost << endl;

  return 0;
}
    
  
