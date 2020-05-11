#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(void)
{
  string s;

  while (cin >> s && s != ".") {
    s += s;
    int len = s.length();

    int i = 0, j = 1;
    for (int k = 0; (i+k < len) && (j+k < len); ++k)
      if (s[i+k] > s[j+k]) {
	i = max(i+k+1, j+1); k = -1;
      }
      else if (s[i+k] < s[j+k]) {
	j = max(j+k+1, i+1); k = -1;
      }

    int period = (i > j) ? i - j : j - i;
    cout << len/2 / period << endl;
  }
  return 0;
}
