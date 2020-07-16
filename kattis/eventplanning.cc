#include <bits/stdc++.h>

// just do it

using namespace std;

int main()
{
  int n, b, h, w;
  cin >> n >> b >> h >> w;

  int best = b+1;
  for (int i = 0; i < h; i++) {
    int p;
    cin >> p;
    for (int j = 0; j < w; j++) {
      int a;
      cin >> a;
      if (n <= a) {
	int total = n * p;
	best = min(best, total);
      }
    }
  }

  if (best <= b) {
    cout << best << endl;
  } else {
    cout << "stay home" << endl;
  }

  return 0;
}
