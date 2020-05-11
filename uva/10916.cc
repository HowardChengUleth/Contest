#include <iostream>
#include <cmath>

using namespace std;

int solve(int year)
{
  int bound = 1 << ((year-1960)/10+2);

  double sum = 0;
  int n = 1;
  while (sum + log2(n+1) < bound) {
    sum += log2(++n);
  }
  return n;
}

int main(void)
{
  int year;

  while (cin >> year && year > 0) {
    cout << solve(year) << endl;
  }
  return 0;
}
