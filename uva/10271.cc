#include <iostream>

using namespace std;

const int MAX_K = 1000+8;
const int MAX_N = 5000;

// best[k][n] = min badness for choosing k pairs from chopstick n..N-1
//              -1 if impossible
long long best[MAX_K+1][MAX_N];
int ind[MAX_K+1][MAX_N];
int badness[MAX_N];

void do_case(void)
{
  int K, N;

  cin >> K >> N;
  K += 8;

  int chop[MAX_N];
  for (int i = 0; i < N; i++) {
    cin >> chop[i];
  }

  for (int n = 0; n < N; n++) {
    best[0][n] = 0;
    ind[0][n] = -1;
    if (n < N) {
      badness[n] = (chop[n+1] - chop[n]) * (chop[n+1] - chop[n]);
    }
  }

  for (int k = 1; k <= K; k++) {
    for (int n = N-1; n >= 0; n--) {
      best[k][n] = -1;          // impossible by default
      ind[k][n] = -1;

      // suppose we do not pick the current pair (n, n+1)
      if (n < N-1 && best[k][n+1] != -1) {
	best[k][n] = best[k][n+1];
	ind[k][n] = 1;
      }

      // suppose we choose the current pair.  Then we need to make sure
      // that we have enough sticks for the longest stick in each triplet.
      // as long as N-n >= 3*k then there must be enough.
      if (N-n >= 3*k && best[k-1][n+2] != -1) {
	long long temp = badness[n] + best[k-1][n+2];
	if (best[k][n] == -1 || best[k][n] > temp) {
	  best[k][n] = temp;
	  ind[k][n] = 2;
	}
      }
    }
  }
  cout << best[K][0] << endl;
  return;
  
  // trace
  int kk = K, nn = 0;
  while (kk >= 0 && nn < N && ind[kk][nn] != -1) {
    if (ind[kk][nn] == 2) {
      cout << "(" << chop[nn] << "," << chop[nn+1] << ")" << endl;
      kk--;
      nn += 2;
    } else if (ind[kk][nn] == 1) {
      nn++;
    }
  }
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    do_case();
  }
  return 0;
}
