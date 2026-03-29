//
// there are only two possibilities:
//
// 1. move the king directly
// 2. spawn a wazir and move it
//
// If the king is already on the spawning point, you would have to move the
// king before spawning...but since the king can move "faster", there is
// never a reason to spawn a wazir in that case.
#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

istream &operator>>(istream &is, pii &p)
{
  return is >> p.first >> p.second;
}

int main()
{
  int n;
  cin >> n;

  pii k, s, t;
  cin >> k >> s >> t;

  // just move the king
  int ans1 = max(abs(k.first-t.first), abs(k.second-t.second));

  // spawn wazir and move
  int ans2 = 1 + abs(s.first-t.first) + abs(s.second-t.second);

  cout << min(ans1, ans2) << endl;


  return 0;
}
