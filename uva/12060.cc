#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int gcd(int a, int b)
{
  if (a < 0) return gcd(-a, b);
  if (b < 0) return gcd(a, -b);
  if (!b) return a;
  return gcd(b, a%b);
}

void print(int num, int den)
{
  string output[3];

  if (num < 0) {
    num *= -1;
    output[0] += "  ";
    output[1] += "- ";
    output[2] += "  ";
  }

  int quo = num / den, rem = num % den;
  if (quo > 0 || rem == 0) {
    string s = to_string(quo);
    output[0] += string(s.length(), ' ');
    output[1] += s;
    output[2] += string(s.length(), ' ');
  }

  if (rem == 0) {
    cout << output[1] << endl;
    return;
  }

  string num_s = to_string(rem), den_s = to_string(den);
  int len1 = num_s.length(), len2 = den_s.length();

  output[0] += string(len2-len1, ' ') + num_s;
  output[1] += string(len2, '-');
  output[2] += den_s;

  for (int i = 0; i < 3; i++) {
    cout << output[i] << endl;
  }
}

bool solve(int id)
{
  int n;
  cin >> n;
  if (!n) return false;
  cout << "Case " << id << ":" << endl;

  int sum = 0;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    sum += x;
  }

  int g = gcd(sum, n);
  sum /= g;
  n /= g;

  print(sum, n);

  
  return true;
}

int main()
{
  int id = 1;

  while (solve(id++))
    ;

  return 0;
}
