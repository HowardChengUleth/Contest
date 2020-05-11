#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool palindrome(int num[], int n)
{
  for (int i = 0, j = n-1; i < j; i++, j--) {
    if (num[i] != num[j]) {
      return false;
    }
  }
  return true;
}

void add1(int next[], int n, int i)
{
  int carry = 0;
  int add = 1;
  while (i < n) {
    carry = (next[i] + add + carry) >= 10;
    next[i] = (next[i] + add + carry) % 10;
    add = 0;
    i++;
  }
}

bool complete(int next[], int n, int pos, int completion[])
{
  fill(completion, completion+n, 0);
  copy(next+pos+1, next+n, completion+pos+1);
  for (int i = 0; i <= pos && n-1-i > pos; i++) {
    completion[i] = completion[n-1-i];
  }
  return palindrome(completion, n);
}

int diff(int completion[], int num[], int n)
{
  int borrow = 0;
  int ans = 0;
  int mult = 1;
  
  for (int i = 0; i < n; i++) {
    int t = completion[i] - borrow - num[i];
    borrow = t < 0;
    ans += ((borrow) ? t + 10 : t) * mult;
    mult *= 10;
  }
  return ans;
}

int solve(const string &s)
{
  int n = s.length();
  int num[9];

  for (int i = 0; i < n; i++) {
    num[i] = s[n-1-i] - '0';
  }

  if (palindrome(num, n)) {
    return 0;
  }
  
  // try adding 1 at each position (up to 9 times)
  // and complete the palindrome
  int completion[9];
  for (int i = 0; i < n; i++) {
    int next[9];
    copy(num, num+9, next);
    for (int j = 1; j <= 9-num[i]; j++) {
      add1(next, n, i);
      if (complete(next, n, i-1, completion)) {
	return diff(completion, num, n);
      }
    }
  }
  fill(completion, completion+n, 0);
  return diff(completion, num, n);
}

int main(void)
{
  string s;

  while (cin >> s && s != "0") {
    cout << solve(s) << endl;
  }

  return 0;
}
