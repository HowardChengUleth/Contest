#include <iostream>

using namespace std;

int fact[13], derange[13];

int main(void)
{
  fact[0] = fact[1] = 1;
  derange[0] = 1;
  derange[1] = 0;
  for (int i = 2; i <= 12; i++) {
    fact[i] = fact[i-1] * i;
    derange[i] = (i-1)*(derange[i-1] + derange[i-2]);
  }

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    cout << derange[n] << '/' << fact[n] << endl;
  }
  
  return 0;
}
