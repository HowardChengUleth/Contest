#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

int iter(int n)
{
  ostringstream oss;
  oss << n;
  return oss.str().length();
}

int main(void)
{
  string num;
  while (cin >> num && num != "END") {
    int prev = -1;
    if (num.length() < 9) {
      prev = atoi(num.c_str());
    }
    int n = num.length();
    int ans = 1;
    while (n != prev) {
      prev = n;
      n = iter(prev);
      ans++;
    }
    cout << ans << endl;
  }

  return 0;
}
