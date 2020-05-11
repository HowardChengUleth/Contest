#include <iostream>

using namespace std;

int main(void)
{
  unsigned long long f[31];
  
  f[0] = 1;
  f[1] = 0;
  for (int n = 2; n <= 30; n++) {
    f[n] = f[n-2];
    for (int j = 2; j <= n; j += 2) {
      f[n] += 2*f[n-j];
    }
  }

  int n;
  while (cin >> n && n >= 0) {
    cout << f[n] << endl;
  }
  return 0;
}
