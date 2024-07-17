#include <bits/stdc++.h>

using namespace std;

bool solve()
{
  int x, y;
  cin >> x >> y;
  if (x == 0 && y == 0) {
    return false;
  }

  if (x + y == 13) {
    cout << "Never speak again." << endl;
  } else if (x > y) {
    cout << "To the convention." << endl;
  } else if (x == y) {
    cout << "Undecided." << endl;
  } else {
    cout << "Left beehind." << endl;
  }
  

  return true;
}

int main()
{
  while (solve())
    ;
  
  return 0;
}
  
