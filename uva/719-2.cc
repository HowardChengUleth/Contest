#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// pos = position of the start of the lexicographically least rotation
// period = the period
void compute(string s, int &pos, int &period)
{
  s += s;
  int len = s.length();
  int i = 0, j = 1;
  for (int k = 0; i+k < len && j+k < len; k++) {
    if (s[i+k] > s[j+k]) {
      i = max(i+k+1, j+1);
      k = -1;
    } else if (s[i+k] < s[j+k]) {
      j = max(j+k+1, i+1);
      k = -1;
    }
  }

  pos = min(i, j);
  period = (i > j) ? i - j : j - i;
}

int main(void)
{
  int n;
  string s;
  cin >> n;
  while (n--) {
    cin >> s;
    int pos, period;
    compute(s, pos, period);
    cout << pos+1 << endl;
  }
  return 0;
}

