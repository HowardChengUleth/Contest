#include <iostream>
#include <algorithm>

using namespace std;

void solve_case(void)
{
  int target;
  cin >> target;

  int n;
  cin >> n;

  int value[100];
  for (int i = 0; i < n; i++) {
    cin >> value[i];
  }

  int bills[20001];
  fill(bills, bills+20001, -1);
  bills[0] = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 20000; j >= value[i]; j--) {
      if (bills[j-value[i]] >= 0 &&
	  (bills[j] == -1 || bills[j-value[i]]+1 < bills[j])) {
	bills[j] = bills[j-value[i]]+1;
      }
    }
  }
  for (int i = target; i <= 20000; i++) {
    if (bills[i] >= 0) {
      cout << i << ' ' << bills[i] << endl;
      return;
    }
  }

}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    solve_case();
  }
  return 0;
}
