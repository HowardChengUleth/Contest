#include <bits/stdc++.h>

using namespace std;

int main()
{
  int prev = INT_MAX;
  int x;
  int count = 0;
  while (cin >> x) {
    if (x > prev) {
      count++;
    }
    prev = x;
  }
  cout << count << endl;
  return 0;
}
