#include <bits/stdc++.h>

using namespace std;

int partition(vector<int> &A, int start, int end, int k)
{
  // reverse logic to sort biggest to smallest
  int i = start+1;
  for (int j = start+1; j < end; j++) {
    int winner;
    cout << "? " << A[j] << ' ' << A[start] << flush << endl;
    cin >> winner;
    assert(winner != -1);
    if (winner == A[j]) {
      swap(A[i++], A[j]);
    }
  }
  swap(A[i-1], A[start]);
  return i-1;
}

void qselect(vector<int> &A, int start, int end, int k)
{
  int pivot = rand() % (end - start) + start;
  swap(A[start], A[pivot]);

  int pos = partition(A, start, end, k);

  if (pos + 1 - start == k || pos - start == k) {
    return;
  } else if (pos - start > k) {
    qselect(A, start, pos, k);
  } else {
    qselect(A, pos+1, end, k - (pos + 1 - start));
  }
}

int main()
{
  int n, k;
  cin >> n >> k;

  vector<int> A(n);
  iota(begin(A), end(A), 1);

  qselect(A, 0, n, k);

  cout << "!";
  for (int i = 0; i < k; i++) {
    cout << ' ' << A[i];
  }
  cout << endl;


  return 0;
}
