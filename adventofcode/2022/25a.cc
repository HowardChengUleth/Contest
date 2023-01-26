#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll fromSNAFU(string line)
{
  ll ans = 0;
  for (auto c : line) {
    int val;
    switch (c) {
    case '2':
      val = 2;
      break;
    case '1':
      val = 1;
      break;
    case '0':
      val = 0;
      break;
    case '-':
      val = -1;
      break;
    case '=':
      val = -2;
      break;
    }
    ans = ans * 5 + val;
  }

  return ans;
}

string toSNAFU(ll x)
{
  if (x == 0) return "";
  
  int d = x % 5;
  if (d > 2) {
    d -= 5;
  }

  char digit_norm[] = { '=', '-', '0', '1', '2' };
  char *digit = digit_norm+2;
  return toSNAFU((x - d)/5) + digit[d];
}

int main()
{
  string line;
  ll sum = 0;
  
  while (getline(cin, line)) {
    sum += fromSNAFU(line);
  }

  cout << sum << endl;
  cout << toSNAFU(sum) << endl;


  return 0;
}
