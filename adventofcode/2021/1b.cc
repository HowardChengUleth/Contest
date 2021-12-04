#include <bits/stdc++.h>

using namespace std;

int main()
{
  vector<int> A;
  int x;
  A.push_back(0);
  while (cin >> x) {
    A.push_back(x);
  }

  vector<int> B(A.size());
  partial_sum(begin(A), end(A), begin(B));

  int count = 0;
  for (int i = 4; i < A.size(); i++) {
    int curr = B[i] - B[i-3];
    int prev = B[i-1] - B[i-4];
    if (curr > prev) {
      count++;
    }
  }

  cout << count << endl;
  
  return 0;
}
