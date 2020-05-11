#include <iostream>
#include <set>

using namespace std;

int happy(int N)
{
  set<int> S;
  int sum;

  while (N != 1) {
    S.insert(N);
    sum = 0;
    while (N > 0) {
      sum += (N % 10) * (N % 10);
      N /= 10;
    }
    if (S.find(sum) != S.end()) {
      return 0;
    }
    N = sum;
  }

  return 1;
}

int main(void)
{
  int cases;
  int N;
  
  cin >> cases;
  for (int i = 0; i < cases; i++) {
    cin >> N;
    cout << "Case #" << i+1 << ": " << N << " is "
	 << (happy(N) ? "a Happy" : "an Unhappy") << " number." << endl;
  }

  return 0;
}
