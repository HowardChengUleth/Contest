#include <algorithm>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int tocdn(int us, double uscdn)
{
  return floor(us * uscdn * 0.97);
}

int tous(int cdn, double uscdn)
{
  return floor(cdn / uscdn * 0.97);
}

bool solve()
{
  int d;
  cin >> d;
  if (!d) return false;

  double uscdn[365];
  for (int i = 0; i < d; i++) {
    cin >> uscdn[i];
  }

  int us[366], cdn[366];
  cdn[0] = 100000;
  us[0] = 0;

  for (int i = 1; i <= d; i++) {
    cdn[i] = max(cdn[i-1], tocdn(us[i-1], uscdn[i-1]));
    us[i] = max(us[i-1], tous(cdn[i-1], uscdn[i-1]));
  }

  cout << cdn[d]/100 << '.' << setw(2) << setfill('0') << cdn[d] % 100 << endl;

  return true;
}

int main()
{
  while (solve())
    ;

  return 0;
}
