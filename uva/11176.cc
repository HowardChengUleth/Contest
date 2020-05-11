#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

bool solve()
{
  int n;
  double p;

  cin >> n >> p;
  if (!n) return false;

  // prob[i][j] = the probability of the longest winning streak <= j playing
  //              i games
  double prob[501][501];

  double powers[501];
  powers[0] = 1;
  for (int i = 1; i <= n; i++) {
    powers[i] = p * powers[i-1];
  }
  
  prob[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    prob[i][0] = (1-p) * prob[i-1][0];
  }
  
  for (int k = 1; k <= n; k++) {
    for (int i = 0; i <= n; i++) {
      if (k >= i) {
	prob[i][k] = 1;
      } else {
	prob[i][k] = 0;
	for (int j = 0; j <= k; j++) {
	  prob[i][k] += powers[j]*(1-p)*prob[i-(j+1)][k];
	}
      }
    }
  }
  
  double expected_len = 0;
  for (int l = 1; l <= n; l++) {
    expected_len += l * (prob[n][l] - prob[n][l-1]);
  }

  cout << fixed << setprecision(6) << expected_len << endl;
  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
