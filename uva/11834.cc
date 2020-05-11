#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
  int L, C, R1, R2;

  while (cin >> L >> C >> R1 >> R2 &&
	 (L || C || R1 || R2)) {
    bool good = max(R1, R2)*2 <= min(L, C);
    L -= (R1+R2);
    C -= (R1+R2);
    good &= L*L + C*C >= (R1+R2)*(R1+R2);
    
    cout << (good ? "S" : "N") << endl;
  }
  return 0;
}
