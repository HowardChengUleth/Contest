#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int n;
  int A[1000];
  int sums[1000*999/2];
  int sums_n;
  int case_num = 1;

  while (cin >> n) {
    cout << "Case " << case_num++ << ":" << endl;
    for (int i = 0; i < n; i++) {
      cin >> A[i];
    }
    sums_n = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) {
	if (A[i] != A[j]) {
	  sums[sums_n++] = A[i]+A[j];
	}
      }
    }

    sort(sums, sums+sums_n);

    int m;
    cin >> m;
    while (m-- > 0) {
      int x;
      cin >> x;
      
      int index = lower_bound(sums, sums+sums_n, x) - sums;
      int best = -1;
      int diff, temp;
      for (int delta = -1; delta <= 1; delta++) {
	if (0 <= index+delta && index+delta < sums_n) {
	  temp = (x > sums[index+delta]) ? x - sums[index+delta] : 
	    sums[index+delta] - x;
	  if (best < 0 || diff > temp) {
	    diff = temp;
	    best = index+delta;
	  }
	}
      }
      cout << "Closest sum to " << x << " is " << sums[best] << "." << endl;
    }
  }
  return 0;
}
