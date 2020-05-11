#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

// possible[i][j] = an integer whose k-th bit (starting from 0) is 1 iff
//                  it is possible to have a subset of size k from
//                  people 1..i summing up to j
unsigned long long possible[101][100*450+1];

int diff(int a, int b)
{
  return (a > b) ? a - b : b - a;
}

void do_case(void)
{
  int n, weight[100];
  int total = 0;
  
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> weight[i];
    total += weight[i];
  }

  for (int i = 0; i <= n; i++) {
    fill(possible[i], possible[i] + total + 1, 0);
  }

  // make sure the subset size is at most (n+1)/2
  unsigned long long mask = (1ULL << ((n+1)/2+1)) - 1;
  
  possible[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= (i-1)*450; j++) {
      possible[i][j] |= possible[i-1][j];
      possible[i][j + weight[i-1]] |= ((possible[i-1][j] << 1) & mask);
    }
  }

  // now we look for the one closest to half with bit n/2 set
  mask = (1ULL << (n/2));
  //  cout << "mask = " << mask << endl;
  int bestdiff = total;
  int bestj = 0;
  for (int j = 1; j <= total-1; j++) {
    for (int i = 0; i <= n; i++) {
      if (possible[i][j] & mask) {
	if (diff(total-j, j) < bestdiff) {
	  bestdiff = diff(total-j, j);
	  bestj = j;
	}
      }
    }
  }
  cout << min(total-bestj, bestj) << ' ' << max(total-bestj, bestj) << endl;
}

int main(void)
{
  int cases;
  cin >> cases;

  while (cases-- > 0) {
    do_case();
    if (cases) {
      cout << endl;
    }
  }

  return 0;
}
