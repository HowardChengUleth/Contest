#include <bits/stdc++.h>

using namespace std;

void erase(multiset<int> &div, int d)
{
  auto it = div.find(d);
  if (it != div.end()) {
    div.erase(it);
  }
}

int main()
{
  int n;
  cin >> n;

  multiset<int> div;
  for (int i = 0; i < n; i++) {
    int d;
    cin >> d;
    div.insert(d);
  }

  int y = *div.rbegin();

  if (y == 1) {
    erase(div, y);
  } else {
    for (int i = 1; i <= y; i++) {
      if (y % i == 0) {
	erase(div, i);
      }
    }
  }
  int x = *div.rbegin();

  cout << x << ' ' << y << endl;
  

  return 0;
}
