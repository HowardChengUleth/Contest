#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int solve()
{
  long long k;
  cin >> k;

  long long tax = 0;

  // first step
  k -= 180000;
  k = max(0LL, k);

  // second step
  tax += (min(k, 300000LL) * 10 + 99)/100;
  k -= min(k, 300000LL);

  // third step
  tax += (min(k, 400000LL) * 15 + 99)/100;
  k -= min(k, 400000LL);

  // fourth step
  tax += (min(k, 300000LL) * 20 + 99)/100;
  k -= min(k, 300000LL);

  // rest
  tax += (k * 25 + 99) / 100;

  // min tax
  if (tax > 0) {
    tax = max(2000LL, tax);
  }
  
  /*
  if (k <= 180000) return 0;
  k -= 180000;

  if (k <= 300000) return max(2000LL,(k * 10 + 99)/100);
  tax += 30000;
  k -= 300000;

  if (k <= 400000) return tax + (k * 15 + 99)/100;
  tax += 60000;
  k -= 400000;

  if (k <= 300000) return tax + (k * 20 + 99)/100;
  tax += 60000;
  k -= 300000;

  tax += (k * 25 + 99) / 100;
  */
  return tax;
}

int main()
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": " << solve() << endl;
  }
  return 0;
}
