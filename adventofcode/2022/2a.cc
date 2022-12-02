#include <bits/stdc++.h>

using namespace std;

int result(int y, int m)
{
  if (y == m) return 1;
  if ((y+1) % 3 == m) return 2;
  return 0;
}

int main()
{
  char yours, mine;
  int total = 0;
  
  while (cin >> yours >> mine) {
    int y = yours - 'A';
    int m = mine - 'X';

    total += m + 1;
    total += result(y, m) * 3;
  }
  cout << total << endl;

  return 0;
}
