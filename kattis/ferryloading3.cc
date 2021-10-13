#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

void do_case()
{
  int n, t, m;
  cin >> n >> t >> m;

  int unloaded[10000];
  fill(unloaded, unloaded+m, -1);
  
  queue<pair<int, int> > wait[2];
  for (int i = 0; i < m; i++) {
    int t;
    string dir;
    cin >> t >> dir;
    if (dir == "left") {
      wait[0].push(make_pair(t, i));
    } else {
      wait[1].push(make_pair(t, i));
    }
  }

  int side = 0;
  int curr_t = 0;

  while (!wait[0].empty() || !wait[1].empty()) {
    // if there is no one on the current side, so go to the other side
    if (wait[side].empty() ||
	(curr_t < wait[side].front().first &&
	 !wait[1-side].empty() &&
	 wait[1-side].front().first < wait[side].front().first)) {
      curr_t = max(curr_t, wait[1-side].front().first) + t;
      side = 1-side;
      continue;
    }

  
    // take the next n cars
    int to_take[10000];
    int num_take = 0;
    curr_t = max(curr_t, wait[side].front().first);
    for (int i = 0; i < n && !wait[side].empty() &&
	   wait[side].front().first <= curr_t; i++) {
      to_take[num_take++] = wait[side].front().second;
      wait[side].pop();
    }

    //    cout << "time = " << curr_t << endl;
    curr_t += t;
    for (int i = 0; i < num_take; i++) {
      unloaded[to_take[i]] = curr_t;
      //      cout << "  taking " << to_take[i] << " from " << side << endl;
    }
    side = 1-side;
  }

  for (int i = 0; i < m; i++) {
    cout << unloaded[i] << endl;
  }
}

int main(void)
{
  int c;
  cin >> c;
  while (c-- > 0) {
    do_case();
    if (c) {
      cout << endl;
    }
  }

  return 0;
}
