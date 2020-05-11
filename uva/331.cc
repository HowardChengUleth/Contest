#include <iostream>
#include <algorithm>

using namespace std;

int inversions(int n, const int A[])
{
  int count = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      count += A[i] > A[j];
    }
  }
  return count;
}

int count_map(int n, int A[], int inv, int base = 0)
{
  if (inv == 0) {
    return base;
  }

  int count = 0;
  for (int i = 0; i < n-1; i++) {
    if (A[i] > A[i+1]) {
      swap(A[i], A[i+1]);
      count += count_map(n, A, inv-1, 1);
      swap(A[i], A[i+1]);
    }
  }
  return count;
}

int main(void)
{
  int n, A[5];
  int num = 1;

  while (cin >> n && n) {
    for (int i = 0; i < n; i++) {
      cin >> A[i];
    }
    
    int inv = inversions(n, A);
    
    cout << "There are " << count_map(n, A, inv) 
	 << " swap maps for input data set " << num++ << "." << endl;
  }
  return 0;
}
