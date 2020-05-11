#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

void solve(int n)
{
  int digits[20];
  int d = 0;
  while (n > 0) {
    digits[d++] = n % 10;
    n /= 10;
  }

  sort(digits, digits+d, greater<int>());
  long long a = 0;
  for (int i = 0; i < d; i++) {
    a = a*10 + digits[i];
  }

  for (int i = d-1; i >= 0; i--) {
    if (digits[i]) {
      swap(digits[0], digits[i]);
      break;
    }
  }
  sort(digits+1, digits+d);
  long long b = 0;
  for (int i = 0; i < d; i++) {
    b = b*10 + digits[i];
  }

  long long diff = a-b;
  cout << a << " - " << b << " = " << diff << " = 9 * " << diff/9 << endl;
}

int main(void)
{
  int n;
  while (cin >> n) {
    solve(n);
  }
  return 0;
}
