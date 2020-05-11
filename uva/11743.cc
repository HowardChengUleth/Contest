//
// Just do it.
//
#include <iostream>

using namespace std;

// this is an overkill: s only has 2 digits...
int digitsum(int s)
{
  int sum = 0;
  while (s) {
    sum += s % 10;
    s /= 10;
  }
  return sum;
}

void do_case()
{
  char ch;
  int sum = 0;

  for (int i = 0; i < 8; i++) {
    cin >> ch;
    sum += digitsum(2*(ch-'0'));
    cin >> ch;
    sum += ch - '0';
  }
  cout << ((sum % 10) ? "Invalid" : "Valid") << endl;
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    do_case();
  }
  return 0;
}
