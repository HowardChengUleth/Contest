#include <iostream>
#include <algorithm>

using namespace std;

// F[N][P] = number of permutations of N people with P people visible from
//           one direction and arbitrary number from the other direction.
//
// we only have to compute up to N = 12 for this problem.
//
const int MAX_N = 12;

int F[MAX_N+1][MAX_N+1];

int factorial[MAX_N+1];

void comp_factorial(void)
{
  factorial[0] = factorial[1] = 1;

  for (int i = 2; i <= MAX_N; i++) {
    factorial[i] = i * factorial[i-1];
  }
}

void compute(int *perm, int n, int start, int visible, int tallest)
{
  if (tallest == n) {
    F[n][visible] += factorial[n-start];
    return;
  }

  for (int i = start; i < n; i++) {
    swap(perm[start], perm[i]);
    if (perm[start] > tallest) {
      compute(perm, n, start+1, visible+1, perm[start]);
    } else {
      compute(perm, n, start+1, visible, tallest);
    }
    swap(perm[start], perm[i]);
  }
}

int main(void)
{
  comp_factorial();
  for (int n = 1; n <= MAX_N; n++) {
    int perm[MAX_N];
    
    for (int i = 1; i <= n; i++) {
      perm[i-1] = i;
    }
    
    cerr << "Computing n = " << n << "...";
    compute(perm, n, 0, 0, 0);
    cerr << "done" << endl;
  }

  cout << "int F[" << MAX_N+1 << "][" << MAX_N+1 << "] = {" << endl;

  for (int n = 0; n <= MAX_N; n++) {
    cout << "  { ";
    for (int p = 0; p <= MAX_N; p++) {
      cout << F[n][p] << ((p < MAX_N) ? ", " : " ");
    }
    cout << "}" << ((n < MAX_N) ? "," : "") << endl;
  }

  cout << "};" << endl;

  return 0;
}
