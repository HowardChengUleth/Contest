// the number of different values before a cycle is found is small
// (9*9^2), so just do it all and try all possible intersection points.

#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int next(int s)
{
  int t = 0;
  while (s > 0) {
    t += (s % 10) * (s % 10);
    s /= 10;
  }
  return t;
}

typedef map<int, int> Map;
typedef Map::iterator MapIt;

void gen(Map &dist, int s)
{
  int step = 1;
  do {
    dist[s] = step++;
    s = next(s);
  } while (dist.find(s) == dist.end());
}

int main()
{
  int A, B;
  while (cin >> A >> B && (A ||B)) {
    Map Adist, Bdist;

    gen(Adist, A);
    gen(Bdist, B);

    bool found = false;
    int best = 1000000000;
    for (MapIt it = Adist.begin(); it != Adist.end(); ++it) {
      if (Bdist.find(it->first) != Bdist.end()) {
	found = true;
	best = min(best, it->second + Bdist[it->first]);
      }
    }
    if (!found) {
      best = 0;
    }
    cout << A << ' ' << B << ' ' << best << endl;
    
  }
  return 0;
}
