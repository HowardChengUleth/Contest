#include <bits/stdc++.h>

using namespace std;

bool leap(int y)
{
  if (y % 400 == 0) return true;
  if (y % 100 == 0 && y % 400 != 0) return false;
  if (y % 4 == 0 && y % 100 != 0) return true;
  return false;
}

bool valid(char digit[8])
{
  const int DIM[2][13] = {
			  { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
			  { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
  };

  int val[8];
  for (int i = 0; i < 8; i++) {
    val[i] = digit[i] - '0';
  }
  
  int y = val[0]*1000+val[1]*100+val[2]*10+val[3];
  int m = val[4]*10+val[5];
  int d = val[6]*10+val[7];

  if (y < 2000) return false;
  if (m == 0 || m > 12) return false;
  if (d == 0) return false;
  
  return d <= DIM[leap(y)][m];
}

void solve()
{
  char digit[8];
  for (int i = 0; i < 8; i++) {
    cin >> digit[i];
  }

  sort(digit, digit+8);
  int count = 0;
  string y, m, d;
  do {
    if (valid(digit)) {
      if (!count) {
	y = string(1,digit[0]) + digit[1] + digit[2] + digit[3];
	m = string(1,digit[4]) + digit[5];
	d = string(1,digit[6]) + digit[7];
      }
      count++;
    }
  } while (next_permutation(digit, digit+8));

  cout << count;
  if (count) {
    cout << ' ' << d << ' ' << m << ' ' << y;
  }
  cout << endl;
}

int main()
{
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
