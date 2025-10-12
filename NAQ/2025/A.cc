#include <bits/stdc++.h>

using namespace std;

int main()
{
  int r, g, b, cr, cg, cb, crg, cgb;

  cin >> r >> g >> b;
  cin >> cr >> cg >> cb;
  cin >> crg >> cgb;

  int rneed = max(r - cr, 0);
  int gneed = max(g - cg, 0);
  int bneed = max(b - cb, 0);

  if (crg < rneed || cgb < bneed) {
    cout << -1 << endl;
    return 0;
  }

  crg -= rneed;
  cgb -= bneed;

  if (crg + cgb < gneed) {
    cout << -1 << endl;
    return 0;
  }

  cout << rneed + gneed + bneed << endl;

  
  return 0;
}
