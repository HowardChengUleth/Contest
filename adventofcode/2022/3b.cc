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
  string s[3];
  for (int i = 0; i < 3; i++) {
    if (!(cin >> s[i])) return -1;
  }

  int freq[100] = {0};

  for (int i = 0; i < 3; i++) {
    for (auto c : s[i]) {
      freq[priority(c)] |= (1 << i);
    }
  }
  int val = find(freq, freq+100, 7) - freq;
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
