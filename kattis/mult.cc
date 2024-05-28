#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  int first = -1;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (first < 0) {
      first = x;
    } else {
      if (x % first == 0) {
	cout << x << endl;
	first = -1;
      }
    }
  }

  
  return 0;
}
