#include <bits/stdc++.h>

using namespace std;

// easiest thing to do is to convert the input to minutes from midnight,
// do computation, and convert back

int main()
{
  int h1, m1, h2, m2;
  char ch;

  cin >> h1 >> ch >> m1 >> h2 >> ch >> m2;

  int t1 = h1*60+m1, t2 = h2*60+m2;
  int mid = (t1+t2)/2;

  int hh = mid/60, mm = mid%60;

  cout << setw(2) << setfill('0') << hh << ':'
       << setw(2) << setfill('0') << mm << endl;

  return 0;
}
