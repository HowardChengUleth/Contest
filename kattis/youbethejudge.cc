#include <iostream>
#include <string>
#include <vector>

using namespace std;

const long long MAX = 1000000000;
int cntr;
vector<string> numbers;

int check_number(const string& s) {
  if (s[0] == '0') return -1;
  for (auto c : s) {
    if (!isdigit(c)) return -1;
  }
  if (s.length() > 10) return -1;
  long long n = stoll(s);
  if (n > MAX) return -1;
  return n;
}

bool isPrime(int n) {
    if (n <= 1)
        return false;
    for (int i = 2; (long long)i*i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

int main () {
    string s[4];
    int num[3];
    bool ok = true;

    ok = ok && (cin >> s[0]);
    ok = ok && (cin >> s[1]);
    ok = ok && (cin >> s[2]);
    ok = ok && !(cin >> s[3]);

    for (int i = 0; ok && i < 3; i++) {
      ok = ok && (num[i] = check_number(s[i])) >= 0;
    }

    ok = ok && num[0] % 2 == 0 && num[0] > 3 && num[0] <= MAX;
    ok = ok && num[0] == num[1] + num[2];
    ok = ok && isPrime(num[1]) && isPrime(num[2]);

    if (ok) cout << "1\n";
    else cout << "0\n";

    return 0;
}
