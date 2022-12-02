#include <bits/stdc++.h>

using namespace std;

int choice(int y, int r)
{
  return (y+r-1+3) % 3;
}

int main()
{
  char yours, mine;
  int total = 0;
  
  while (cin >> yours >> mine) {
    int y = yours - 'A';
    int r = mine - 'X';
    int m = choice(y, r);

    total += m + 1;
    total += r * 3;
  }
  cout << total << endl;

  return 0;
}
