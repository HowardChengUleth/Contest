#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct State {
  int d[4];

  int index(void) const {
    return d[3]*1000+d[2]*100+d[1]*10+d[0];
  }

  State left(int button) const
  {
    State s(*this);
    if (++s.d[button] == 10) {
      s.d[button] = 0;
    }
    return s;
  }

  State right(int button) const
  {
    State s(*this);
    if (--s.d[button] < 0) {
      s.d[button] = 9;
    }
    return s;
  }			      

  bool operator==(const State &s) const
  {
    for (int i = 0; i < 4; i++) {
      if (d[i] != s.d[i]) return false;
    }
    return true;
  }
};


istream &operator>>(istream &is, State &s)
{
  for (int i = 0; i < 4; i++) {
    is >> s.d[i];
  }
  return is;
}

int search(const State &init, const State &target, bool *forbidden)
{
  queue<State> q;
  int dist[10000];

  fill(dist, dist+10000, -1);
  dist[init.index()] = 0;
  q.push(init);
  while (!q.empty()) {
    State s = q.front();
    q.pop();

    if (s == target) {
      return dist[s.index()];
    }

    for (int i = 0; i < 4; i++) {
      State next = s.left(i);
      if (!forbidden[next.index()] && dist[next.index()] == -1) {
	dist[next.index()] = dist[s.index()]+1;
	q.push(next);
      }
      next = s.right(i);
      if (!forbidden[next.index()] && dist[next.index()] == -1) {
	dist[next.index()] = dist[s.index()]+1;
	q.push(next);
      }
    }
  }
  
  return -1;
}

int main(void)
{
  int N;
  bool forbidden[10000];

  cin >> N;
  while (N-- > 0) {
    State init, target;

    cin >> init >> target;

    fill(forbidden, forbidden+10000, false);
    int n;
    cin >> n;
    while (n-- > 0) {
      State s;
      cin >> s;
      forbidden[s.index()] = true;
    }

    cout << search(init, target, forbidden) << endl;


  }
  return 0;
}
