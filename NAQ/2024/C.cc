#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  int count = 0;
  for (int i = 0; i < n; i++) {
    int d;
    cin >> d;
    count += d % 2;
  }

  cout << count << endl;

  return 0;
}
