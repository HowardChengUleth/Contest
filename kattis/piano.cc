#include <bits/stdc++.h>

using namespace std;

bool weekend(int x)
{
  return x % 7 == 0 || x % 7 == 6;
}

typedef pair<int,int> Interval;

int m, p;
vector<Interval> interval;

bool can_do(bool use_weekend)
{
  // remember the last day each piano needs to be moved, but we will
  // sort it based on earlier last day
  priority_queue<int, vector<int>, greater<int>> pianos;   
  int interval_index = 0;
  
  // try one day at a time, and keep track of pianos that still have to moved
  for (int day = 1; day <= 100; day++) {
    if (!use_weekend && weekend(day))
      continue;

    // add all the pianos that need to be moved
    while (interval_index < m && interval[interval_index].first <= day) {
      pianos.push(interval[interval_index++].second);
    }

    // now moved as many as we can
    for (int i = 0; 2*(i+1) <= p && !pianos.empty(); i++) {
      if (pianos.top() < day) {
	return false;
      }
      
      pianos.pop();
    }
  }

  return pianos.empty();

}

void solve()
{
  cin >> m >> p;
  interval.resize(m);
  
  for (int i = 0; i < m; i++) {
    cin >> interval[i].first >> interval[i].second;
  }
  sort(begin(interval), end(interval));

  if (can_do(false)) {
    cout << "fine" << endl;
  } else if (can_do(true)) {
    cout << "weekend work" << endl;
  } else {
    cout << "serious trouble" << endl;
  }
}

int main()
{
  int n;
  cin >> n;

  while (n--) {
    solve();
  }

  return 0;
}
