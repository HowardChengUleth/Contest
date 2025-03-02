#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  int ac = 0, wa = 0;
  for (int i = 0; i < n; i++) {
    int s;
    cin >> s;

    if (s > 0) {
      ac++;
      wa += s-1;
    } else if (s < 0) {
      wa += -s;
    }
  }

  if (ac > n/2) {
    cout << "easy" << endl;
  } else if (5*ac < n) {
    cout << "hard" << endl;
  } else if (wa > 2*ac) {
    cout << "tricky" << endl;
  } else {
    cout << "medium" << endl;
  }

  return 0;
}
