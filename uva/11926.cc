// use an array with a boolean variable for each minute, and see if we
// have a collision.  Note that for each case we only need to do a constant
// multiple of 1000000 iterations, as long as we stop checking when a
// conflict is found.  That is because we only keep going when there is
// no conflict, and you can only turn each minute from off to on once.
//
// I use STL heavily here, but you can always write your own loops for
// fill and find if you wish.
#include <iostream>
#include <algorithm>

using namespace std;

bool do_case()
{
  int m, n;
  cin >> n >> m;
  if (!n && !m) return false;
  
  // initialize the slots
  int slot[1000001];
  fill(slot, slot+1000001, 0);

  bool good = true;
  for (int i = 0; i < n; i++) {
    int s, e;
    cin >> s >> e;
    if (!good) continue;     // don't do anything if we already have conflict

    // if there is no conflict, fill it
    if (good &= (find(slot+s, slot+e, 1) == slot+e)) {
      fill(slot+s, slot+e, 1);
    }
  }

  for (int i = 0; i < m; i++) {
    int s, e, r;
    cin >> s >> e >> r;

    // don't do anything if we already have conflict
    while (s <= 1000000 && good) {
      // make sure we don't go out of bounds
      e = min(e, 1000001);
      if (good &= (find(slot+s, slot+e, 1) == slot+e)) {
	fill(slot+s, slot+e, 1);
      }
      s += r;
      e += r;
    }
  }
  if (good) {
    cout << "NO CONFLICT" << endl;
  } else {
    cout << "CONFLICT" << endl;
  }
  
  return true;
}

int main(void)
{
  while (do_case())
    ;
  return 0;
}
