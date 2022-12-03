#include <bits/stdc++.h>

using namespace std;

int priority(char c)
{
  if (isupper(c)) {
    return c - 'A' + 27;
  } else {
    return c - 'a' + 1;
  }
}

int solve()
{
  string s;
  if (!(cin >> s)) {
    return -1;
  }
  
  int n = s.length();
  int n2 = n/2;

  int freq[100] = {0};
  for (int i = 0; i < n2; i++) {
    freq[priority(s[i])] |= 1;
  }
  for (int i = n2; i < n; i++) {
    freq[priority(s[i])] |= 2;
  }
  
  int val = find(freq, freq+100, 3) - freq;
  assert(val > 0);
  return val;

}

int main()
{
  string s;
  int total = 0;
  int val;
  while ((val = solve()) > 0) {
    total += val;
  }
  cout << total << endl;
  return 0;
}
