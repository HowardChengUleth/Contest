#include <iostream>
#include <algorithm>

using namespace std;

// F[N][P] = number of permutations of N people with P people visible from
//           one direction and arbitrary number from the other direction.
//
// we only have to compute up to N = 12 for this problem.
//
const int MAX_N = 12;

int F[13][13] = {
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 2, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 6, 11, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 24, 50, 35, 10, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 120, 274, 225, 85, 15, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 720, 1764, 1624, 735, 175, 21, 1, 0, 0, 0, 0, 0 },
  { 0, 5040, 13068, 13132, 6769, 1960, 322, 28, 1, 0, 0, 0, 0 },
  { 0, 40320, 109584, 118124, 67284, 22449, 4536, 546, 36, 1, 0, 0, 0 },
  { 0, 362880, 1026576, 1172700, 723680, 269325, 63273, 9450, 870, 45, 1, 0, 0 },
  { 0, 3628800, 10628640, 12753576, 8409500, 3416930, 902055, 157773, 18150, 1320, 55, 1, 0 },
  { 0, 39916800, 120543840, 150917976, 105258076, 45995730, 13339535, 2637558, 357423, 32670, 1925, 66, 1 }
};

int binom[MAX_N+1][MAX_N+1];

void compute_binom(void)
{
  for (int n = 0; n <= MAX_N; n++) {
    binom[n][0] = binom[n][n] = 1;
    for (int k = 1; k < n; k++) {
      binom[n][k] = binom[n-1][k] + binom[n-1][k-1];
    }
  }
}

int compute(int N, int P, int R)
{
  /* try putting the tallest person in every position possible */
  int ans = 0;

  for (int pos = P-1; pos <= N-R; pos++) {
    ans += binom[N-1][pos] * F[pos][P-1] * F[N-1-pos][R-1];
  }
  
  return ans;
}

int main(void)
{
  int cases;
  
  cin >> cases;

  compute_binom();
  while (cases-- > 0) {
    int N, P, R;
    cin >> N >> P >> R;
    cout << compute(N, P, R) << endl;
  }
  return 0;
}
