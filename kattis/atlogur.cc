#include <bits/stdc++.h>

using namespace std;

int n;
int h[1000], s[1000];

int fight(int chal, int other)
{
  while (true) {
    h[other] -= s[chal];
    if (h[other] <= 0) {
      return chal;
    }

    h[chal] -= s[other];
    if (h[chal] <= 0) {
      return other;
    }
  }
}

int main()
{
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> h[i] >> s[i];
  }

  int challenger = 0;
  for (int i = 1; i < n; i++) {
    challenger = fight(challenger, i);
  }

  cout << challenger+1 << endl;
  return 0;
}
