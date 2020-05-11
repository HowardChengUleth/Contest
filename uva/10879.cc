#include <iostream>

using namespace std;

void solve(int A, int B)
{
  if (B % 2 == 0) {
    cout << 2*A << " * " << B/2 << endl;
  } else {
    for (long long d = 3; d*d <= B; d += 2) {
      if (B % d == 0) {
	cout << d*A << " * " << B/d << endl;
	return;
      }
    }
  }
}

void solve(int K)
{
  if (K % 2 == 0) {
    cout << "2 * " << K/2 << " = ";
    solve(2, K/2);
  } else {
    for (long long d = 3; d*d <= K; d += 2) {
      if (K % d == 0) {
	cout << d << " * " << K/d << " = ";
	solve(d, K/d);
	return;
      }
    }
  }
}

int main(void)
{
  int T;
  cin >> T;

  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";

    int K;
    cin >> K;
    
    cout << K << " = ";
    solve(K);
  }

  return 0;
}
