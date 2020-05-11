#include <iostream>

using namespace std;

bool calc_coeff(long long N, long long len,
		long long& coeffA, long long& coeffB)
{
  long long A[2][2] = {{1,0},{0,1}};

  for (int i = 0; i < N-1; i++) {
    if (A[0][0] + A[1][0] > len || A[0][1] + A[1][1] > len) {
      return false;
    }

    long long a00 = A[0][0], a01 = A[0][1];
    A[0][0] = A[1][0];
    A[0][1] = A[1][1];
    A[1][0] += a00;
    A[1][1] += a01;
  }
  
  coeffA = A[0][0] + A[1][0];
  coeffB = A[0][1] + A[1][1];
  return true;
}

long long calc_length(long long na, long long nb, long long K)
{
  long long m = 1000000007;

  long long x[2][2] = {{0,1},{1,1}};
  long long res[2][2] = {{1,0},{0,1}};
  long long n = K-1;
  while (n > 0) {
    if (n & 0x01) {
      n--;
      long long r00 = res[0][0], r01 = res[0][1],
	r10 = res[1][0], r11 = res[1][1];
      res[0][0] = (r00*x[0][0]%m + r01*x[1][0]%m) % m;
      res[0][1] = (r00*x[0][1]%m + r01*x[1][1]%m) % m;
      res[1][0] = (r10*x[0][0]%m + r11*x[1][0]%m) % m;
      res[1][1] = (r10*x[0][1]%m + r11*x[1][1]%m) % m;
    } else {
      n >>= 1;
      long long x00 = x[0][0], x01 = x[0][1], x10 = x[1][0], x11 = x[1][1];
      x[0][0] = (x00*x00%m + x01*x10%m) % m;
      x[0][1] = (x00*x01%m + x01*x11%m) % m;
      x[1][0] = (x10*x00%m + x11*x10%m) % m;
      x[1][1] = (x10*x01%m + x11*x11%m) % m;
    }
  }

  return (((res[0][0] + res[1][0]) % m * na) % m +
	  ((res[0][1] + res[1][1]) % m * nb) % m) % m;
}

void solve()
{
  long long N, M, X, Y, K;
  cin >> N >> X >> M >> Y >> K;
 
  long long A[2][2];
  if (!(calc_coeff(N, X, A[0][0], A[0][1]) &&
	calc_coeff(M, Y, A[1][0], A[1][1]))) {
    cout << "Impossible" << endl;
    return;
  }

  long long det = A[0][0] * A[1][1] - A[1][0] * A[0][1];
  long long na = X * A[1][1] - Y * A[0][1];
  long long nb = A[0][0] * Y - A[1][0] * X;
  if (det < 0) {
    det *= -1;
    na *= -1;
    nb *= -1;
  }
  
  if (det == 0 || na % det != 0 || nb % det != 0 || na < 0 || nb < 0) {
    cout << "Impossible" << endl;
    return;
  }
  na /= det;
  nb /= det;
  
  cout << calc_length(na, nb, K) << endl;
}

int main(void)
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }

  return 0;
}
