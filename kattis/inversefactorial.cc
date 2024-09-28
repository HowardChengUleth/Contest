#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;


int main()
{
  string fact[8] = {"","1","2","6","24","120","720","5040"};

  string s;
  cin >> s;
  int len = s.length();

  int index = find(fact, fact+8, s) - fact;
  if (index < 8) {
    cout << index << endl;
    return 0;
  }

  long double d = 0.0;
  for (int i = 1; true; i++) {
    d += log10((long double) i);
    int d2 = floor(d) + 1;
    if (d2 == len) {
      cout << i << endl;
      return 0;
    }
  }

  

}
