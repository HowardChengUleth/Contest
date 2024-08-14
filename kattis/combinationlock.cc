#include <bits/stdc++.h>

using namespace std;

bool solve()
{
  int start, d1, d2, d3;
  cin >> start >> d1 >> d2 >> d3;
  if (start == 0 && d1 == 0 && d2 == 0 && d3 == 0) {
    return false;
  }

  int angle = 360*2;
  angle += (start >= d1) ? (start-d1)*9 : (start+40-d1)*9;
  angle += 360;
  angle += (d1 < d2) ? (d2-d1)*9 : (d2+40-d1)*9;
  angle += (d2 > d3) ? (d2-d3)*9 : (d2+40-d3)*9;
  cout << angle << endl;

  return true;
}

int main()
{

  while (solve())
    ;
  
  return 0;
}
