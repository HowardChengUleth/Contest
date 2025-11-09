#include <bits/stdc++.h>

using namespace std;

const int MAX_W = 2000;
const int MAX_K = 2000;

int W, K, C;
int memo[MAX_W+1][MAX_K+1];

bool exactsum(int W, int K)
{
  // just make the wishes
  if (W == K) {
    return true;
  }

  // we can make too many wishes
  if (W < K) {
    return false;
  }

  int &ans = memo[W][K];
  if (ans != -1) {
    return memo[W][K];
  }
  
  for (int k2 = 1; k2 <= K-C; k2++) {
    // make K-1 real wishes and then wish for another genie of rank k2
    if (exactsum(W-(K-1), k2)) {
      return ans = true;
    }
  }

  return ans = false;
}

int main()
{
  cin >> W >> K >> C;

  for (int i = 0; i <= W; i++) {
    for (int j = 0; j <= K; j++) {
      memo[i][j] = -1;
    }
  }

  if (exactsum(W, K)) {
    cout << "yes" << endl;
  } else {
    cout << "no" << endl;
  }
  
  return 0;
}
