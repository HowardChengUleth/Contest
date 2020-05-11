#include <iostream>
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

int main()
{
  int y, m, d, inc;

  while (cin >> inc >> d >> m >> y && (inc || d || m || y)) {
    add_days(y, m, d, inc);
    cout << d << ' ' << m << ' ' << y << endl;
  }
  return 0;
}
