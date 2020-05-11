// This is bubble sort in disguise.  In normal bubble sort, we "bubble up"
// the comparison in a pair of consecutive elements from the left end to 
// the right end of the array.
//
// Instead of moving the pair up, we can instead rotate the sequence down
// and compare the first pair to do the same thing.
//

#include <iostream>
#include <algorithm>

using namespace std;

bool do_case()
{
  int n;
  cin >> n;
  if (!n) return false;

  int invperm[500];
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    invperm[x-1] = i;     // make sure we sort the "inverse" of the permutation
  }

  // total number of ops is <= 2*(n-1)^2 + n <= 2*n^2
  for (int pass = 0; pass < n-1; pass++) {
    // bubble up by rotating
    for (int i = 0; i < n-1; i++) {
      // the inner loop gives at most 2*(n-1)^2 ops
      if (invperm[i] > invperm[i+1]) {
	swap(invperm[i], invperm[i+1]);
	cout << 1;
      }
      cout << 2;
    }

    // rotate once more to start again from the beginning

    // we get exactly n-1 ops here
    cout << 2;
  }

  cout << endl;
  return true;
}

int main(void)
{
  while (do_case())
    ;

  return 0;
}
