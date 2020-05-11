#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int daysInMonth[2][13] = {
  { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
  { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

bool leap(int yr)
{
  return (yr % 400 == 0 || (yr % 4 == 0 && yr % 100 != 0));
}

int daysInYear(int yr)
{
  return leap(yr) ? 366 : 365;
}

void add_days(int &y, int &m, int &d, int inc)
{
  if (inc == 0) {
    return;
  }

  if (m != 1 || d != 1) {
    int t = min(inc, daysInMonth[leap(y)][m] - d);
    d += t;
    inc -= t;
    if (inc > 0) {
      inc--;
      m++;
      d = 1;
      if (m > 12) {
	m = 1;
	y++;
      }
    }
    add_days(y, m, d, inc);
    return;
  }

  while (m == 1 && d == 1 && inc >= daysInYear(y)) {
    inc -= daysInYear(y);
    y++;
  }

  while (inc >= daysInMonth[leap(y)][m]) {
    inc -= daysInMonth[leap(y)][m];
    m++;
  }
  d += inc;
}

void solve(int id)
{
  char ch1, ch2;

  cin >> ch1 >> ch2;
  int m = (ch1-'0')*10+(ch2-'0');

  cin >> ch1 >> ch2;
  int d = (ch1-'0')*10+(ch2-'0');

  cin >> ch1 >> ch2;
  int y = (ch1-'0')*10+(ch2-'0');
  cin >> ch1 >> ch2;
  y = 100*y + (ch1-'0')*10+(ch2-'0');

  add_days(y, m, d, 40*7);
  string zodiac;

  switch (m) {
  case 1:
    zodiac = (d <= 20) ? "capricorn" : "aquarius";
    break;
  case 2:
    zodiac = (d <= 19) ? "aquarius" : "pisces";
    break;
  case 3:
    zodiac = (d <= 20) ? "pisces" : "aries";
    break;
  case 4:
    zodiac = (d <= 20) ? "aries" : "taurus";
    break;
  case 5:
    zodiac = (d <= 21) ? "taurus" : "gemini";
    break;
  case 6:
    zodiac = (d <= 21) ? "gemini" : "cancer";
    break;
  case 7:
    zodiac = (d <= 22) ? "cancer" : "leo";
    break;
  case 8:
    zodiac = (d <= 21) ? "leo" : "virgo";
    break;
  case 9:
    zodiac = (d <= 23) ? "virgo" : "libra";
    break;
  case 10:
    zodiac = (d <= 23) ? "libra" : "scorpio";
    break;
  case 11:
    zodiac = (d <= 22) ? "scorpio" : "sagittarius";
    break;
  case 12:
    zodiac = (d <= 22) ? "sagittarius" : "capricorn";
    break;
  }

  
  cout << id << ' ' << setw(2) << setfill('0') << m << '/'
       << setw(2) << setfill('0') << d << '/' << y << ' ' << zodiac << endl;
}


int main()
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    solve(i);
  }
  return 0;
}
