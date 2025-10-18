#include <bits/stdc++.h>

using namespace std;

int main()
{
  int k, n, m;
  cin >> k >> n >> m;

  vector<int> h(k+1);
  for (int i = 0; i < k; i++) {
    cin >> h[i];
  }
  h[k] = INT_MAX;                // add an extra point of "infinity"

  int sb, sf;
  cin >> sb >> sf;

  int bi = 0;
  int fi = find(begin(h), end(h), sf) - begin(h);

  bool moved;
  do {
    moved = false;
    
    // try to move lower leg
    int h2 = h[bi+1];
    int diff = sf - h2;
    if (n <= diff && diff <= m) {
      bi++;
      sb = h2;
      moved = true;
      continue;
    }
    
    // try to move upper leg
    h2 = h[fi+1];
    diff = h2 - sb;
    if (n <= diff && diff <= m) {
      fi++;
      sf = h2;
      moved = true;
    }
  } while (moved);
    
  cout << sf << endl;

  return 0;
}
