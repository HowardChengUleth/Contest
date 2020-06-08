#include <bits/stdc++.h>

using namespace std;

// the idea is to pretend that there is an infinite array that can grow both
// ways.  We maintain two indices left and right that know where the next book
// on the left or right goes.  The indices can go negative as well, and we will
// remember where each book is.  That way we can calculate the query easily.

int main()
{
  int q;
  cin >> q;

  int left = 0, right = 1;
  int index[200001];

  for (int i = 0; i < q; i++) {
    char ch;
    int id;
    cin >> ch >> id;
    if (ch == 'L') {
      index[id] = left--;
    } else if (ch == 'R') {
      index[id] = right++;
    } else {
      int toleft = index[id] - left;
      int toright = right - index[id];
      cout << min(toleft, toright) - 1 << endl;
    }
  }

  return 0;
}
