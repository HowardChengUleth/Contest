#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int sasc_seq(vector<int> &A, int n, vector<int> &S)
{
  vector<int> last(n+1), pos(n+1), pred(n);
  if (n == 0) {
    return 0;
  }

  int len = 1;
  last[1] = A[pos[1] = 0];

  for (int i = 1; i < n; i++) {
    int j = lower_bound(last.begin()+1, last.begin()+len+1, A[i]) -
      last.begin();
    pred[i] = (j-1 > 0) ? pos[j-1] : -1;
    last[j] = A[pos[j] = i];
    len = max(len, j);
  }

  int start = pos[len];
  for (int i = len-1; i >= 0; i--) {
    S[i] = A[start];
    start = pred[start];
  }

  return len;
}

int main(void)
{
  int x;
  vector<int> v, S;

  while (cin >> x) {
    v.push_back(x);
    S.push_back(x);
  }

  int len = sasc_seq(v, v.size(), S);
  cout << len << endl << "-" << endl;
  for (int i = 0; i < len; i++) {
    cout << S[i] << endl;
  }

  return 0;
}
