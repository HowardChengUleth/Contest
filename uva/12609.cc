//
// Idea: for every N, if N is not divisible by 4 you only have to add
// one extra digit.  You can figure out the length of the digits for
// all 1-digit N, 2-digit N, etc.  Once you figured out which "chunk"
// you are in, then you can skip ahead to k-digit N.  Within all the
// k-digit Ns, you can easily figure out which group of 4 N's it must
// involve, and then you can just step through them.
//

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// the string for N <= 99
string digits1to2;

long long A(long long N)
{
  if (N % 4 == 0) return N;

  // we can be a lot smarter here, but who cares
  for (int i = 0; i <= 9; i++) {
    if ((N*10+i) % 4 == 0) return N*10+i;
  }
  assert(false);
  return -1;
}

void init()
{
  ostringstream oss;
  for (int N = 1; N <= 99; N++) {
    oss << A(N);
  }
  digits1to2 = oss.str();
}

long long pow10(int n)
{
  long long ans = 1;
  while (n-- > 0) {
    ans *= 10;
  }
  return ans;
}

// how long is the string concatenating all A[N] where N has the specified
// digits (>= 3)
long long len(int d)
{
  long long num = pow10(d) - pow10(d-1);   // number of N with d digits

  // multiples of 4 have d digits, others need one more digit appended
  long long mult4 = num/4;
  return d*num + (num - mult4);
}

void solve(long long K)
{
  K--;
  if (K < digits1to2.length()) {
    cout << digits1to2[K] << endl;
    return;
  }
  K -= digits1to2.length();

  // let's see how many digits N has
  int d = 3;
  while (K >= len(d)) {
    K -= len(d);
    d++;
  }

  // let's see how many groups of 4 we have to skip: each group of 4 has
  // 4d+3 digits
  long long group = K / (4*d+3);
  K %= (4*d+3);
  long long startN = pow10(d-1) + 4*group;

  ostringstream oss;
  for (int i = 0; i < 4; i++) {
    oss << A(startN+i);
  }
  string s = oss.str();
  cout << s[K] << endl;
}

int main()
{
  init();
  long long K;
  while (cin >> K && K > 0) {
    solve(K);
  }

  return 0;
}
