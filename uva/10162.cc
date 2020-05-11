/*
 * The sequence i^i mod 10 cycles after 20 steps, because 
 *
 *    i^i = (i mod 10)^(i mod 4) mod 10
 *
 * Furthermore, the sum of the first 20 i^i is 8 mod 10, so the sum is
 * 0 mod 10 for every 100.  Therefore we only need to worry about the
 * last two digits of N.
 *
 */

#include <iostream>
#include <string>

using namespace std;

int main(void)
{
  string line;
  int iexpi[20] = {
    1, 4, 7, 6, 5, 6, 3, 6, 9, 0, 1, 6, 3, 6, 5, 6, 7, 4, 9, 0
  };          // i^i mod 10 from 1 to 20, cycles after that.

  while (cin >> line && line != "0") {
    int N = line[line.length()-1]-'0';
    if (line.length() > 1) {
      N += 10*(line[line.length()-2]-'0');
    }
    
    int digit = 0;
    int k = 0;
    while (N-- > 0) {
      digit = (digit + iexpi[k]) % 10;
      k = (k+1) % 20;
    }
    cout << digit << endl;
  }


  return 0;
}
