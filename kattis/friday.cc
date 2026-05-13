#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int D, M;
  cin >> D >> M;

  vector<int> daysInMonth(M);
  for (auto &x : daysInMonth) {
    cin >> x;
  }

  int f13 = 0;
  int curr_day = 0;      // 0-based current month and day
  int curr_month = 0;
  
  for (int d = 0; d < D; d++) {
    f13 += (curr_day == 12 && d % 7 == 5);

    if (++curr_day == daysInMonth[curr_month]) {
      curr_month++;
      curr_day = 0;
    }
  }

  cout << f13 << endl;

}

int main()
{
  int T;
  cin >> T;

  while (T--) {
    solve();
  }

  return 0;
}
