#include <bits/stdc++.h>

using namespace std;

bool isLeap(int y)
{
  return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}

string names[13] = {
  "", "January", "February", "March", "April",
  "May", "June", "July", "August", "September",
  "October", "November", "December"
};

void solve()
{
  int m1, d1, y1, m2, d2, y2;
  string s1, s2, comma;

  cin >> s1 >> d1 >> comma >> y1;
  cin >> s2 >> d2 >> comma >> y2;

  m1 = find(names, names+13, s1) - names;
  m2 = find(names, names+13, s2) - names;

  int ans = 0;

  // move to January 1
  if (m1 > 2 && isLeap(y1)) {
    ans--;
  }
  if ((m2 > 2 || (m2 == 2 && d2 == 29)) && isLeap(y2)) {
    ans++;
  }

  // how many are multiples of 4?
  ans += (y2+3)/4 - (y1+3)/4;

  // how many are multiples of 100?
  ans -= (y2+99)/100 - (y1+99)/100;

  // how many are multiples of 400?
  ans += (y2+399)/400 - (y1+399)/400;
  
  cout << ans << endl;
}


int main()
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    solve();
  }
  
  return 0;
}
