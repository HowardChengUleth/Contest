#include <iostream>  
#include <cmath>  
#include <algorithm>

using namespace std;  

bool square(int n)
{
  int i = 1, isq = 1;

  while (isq < n) {
    isq += 2*i+1;
    i++;
  }

  return isq == n;
}

void solve(int N)
{
  int peg[51];
  int done = 0, curr = 1;
  
  fill(peg, peg+N, 0);
  while (!done) {
    done = 1;
    for (int i = 0; i < N && done; i++) {
      if (!peg[i] || square(peg[i]+curr)) {
	peg[i] = curr++;
	done = 0;
      }
    }
  }
  cout << curr-1 << endl;
}
 
int main(void)
{
  int T;

  cin >> T;
  while (T-- > 0) {
    int N;
    cin >> N;
    solve(N);
  }
  
  return 0;
}


