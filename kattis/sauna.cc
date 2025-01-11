#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;
  
  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i] >> B[i];
  }

  int lower = *max_element(begin(A), end(A));
  int upper = *min_element(begin(B), end(B));

  if (lower > upper) {
    cout << "bad news" << endl;
  } else {
    cout << (upper-lower+1) << ' ' << lower << endl;
  }

  return 0;
}
