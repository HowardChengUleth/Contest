#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

// factors[n] = # of factors in n!

const int MAX_X = 3000000;
int factors[MAX_X+1];
int ppower[MAX_X+1];


int main(void)
{
  factors[0] = factors[1] = 0;
  fill(ppower+2, ppower+MAX_X+1, 0);
  
  for (int d = 2; d <= MAX_X; d++) {
    if (ppower[d] < 0) continue;

    for (int i = d; i <= MAX_X; i += d) {
      factors[i]++;
      if (ppower[i] == 0) {
	ppower[i] = d;
      } else if (ppower[i] > 0 && d % ppower[i] != 0) {
	ppower[i] = -1;
      }
    }
  }
  partial_sum(factors+2, factors+MAX_X+1, factors+2);

  int N;
  int case_num = 1;
  while (cin >> N && N >= 0) {
    int pos = lower_bound(factors, factors+MAX_X+1, N) - factors;
    cout << "Case " << case_num++ << ": ";
    if (factors[pos] == N) {
      cout << pos << "!" << endl;
    } else {
      cout << "Not possible." << endl;
    }
  }
  
  return 0;
}
