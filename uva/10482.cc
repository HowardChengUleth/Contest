#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

struct State
{
  int a[3];

  State()
  {
    fill(a, a+3, 0);
  }

  State(const State &s)
  {
    copy(s.a, s.a+3, a);
  }

  State &operator=(const State &s)
  {
    copy(s.a, s.a+3, a);
    return *this;
  }
  
  // only really 640^2 entries because the sum is fixed
  int toint() const
  {
    return (a[0]*640+a[1])*640+a[2];
  }

  bool operator<(const State &s) const
  {
    return toint() < s.toint();
  }

  void add(int idx, int amt)
  {
    a[idx] += amt;
    sort(a, a+3);
  }

  int score() const
  {
    return a[2] - a[0];
  }
};

void solve()
{
  int n;
  int A[32];
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> A[i];
  }

  set<State> curr;
  State s;
  curr.insert(s);

  for (int i = 0; i < n; i++) {
    set<State> next;

    for (set<State>::const_iterator it = curr.begin(); it != curr.end(); ++it) {
      State n = *it;
      n.add(0, A[i]);
      next.insert(n);
      n = *it;
      n.add(1, A[i]);
      next.insert(n);
      n = *it;
      n.add(2, A[i]);
      next.insert(n);
    }
    curr = next;
  }

  int best = -1;
  for (set<State>::const_iterator it = curr.begin(); it != curr.end(); ++it) {
    if (best < 0 || it->score() < best) {
      best = it->score();
    }
  }
  cout << best << endl;
}

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    solve();
  }

  return 0;
}
