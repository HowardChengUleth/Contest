/* @JUDGE_ID: 1102NT 113 C++ "" */

#include <iostream>
#include <cmath>
#include <cfloat>

using namespace std;

int main(void)
{
  long double n;
  long double p;   // gives 18 digits...should be okay since k only gives
                   // 9 digits, and we know k exists
  long double k;

  while (cin >> n >> p) {
    k = floor(pow(p, 1.0/n)+0.5);
    cout << static_cast<int>(k) << endl;
  }

  return 0;
}
