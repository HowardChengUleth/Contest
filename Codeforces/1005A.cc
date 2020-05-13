#include <bits/stdc++.h>
     
using namespace std;

// the number of stairways climbed is actaully just the number of 1's
// in the sequence
//
// to know the number of steps in each stairways, we just have to look at
// each number before resetting to 1 in the next step (taking care of the
// very last case

int A[1001];
int main()
{
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> A[i];
  }
  A[n] = 1;        // add 1 at the end to catch the last stairway
     
  cout << count(A, A+n, 1) << endl;
      
  for (int i = 1; i < n+1; i++) {
    if (A[i] == 1) cout << A[i-1] << ' ';
  }
      
  cout << endl;
  return 0;
}
