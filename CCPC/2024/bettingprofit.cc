#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;
  while (n--) {
    double bet, odds;
    char sign;
    double profit;
    
    cin >> bet >> odds >> sign;
    if (sign == '+') {
      profit = bet / 100.0 * odds;
    } else {
      profit = bet / odds * 100;
    }
    cout << fixed << setprecision(10) << profit << endl;

  }

  return 0;
}
