#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

// There are at most 100 elevators and each stopping at at most 1000
// floors, so there are a total of 10^5 floors that we care about.
// Anything in between, or the bottom and top floor if it is not covered,
// has to be reached by going to the cheapest elevator and walk.
//
// So for each elevator we generate all floors that it touches.  For each
// pair of elevators we can determine how many floors you have to walk to
// switch from one to another.  Because these lists are sorted, we can
// process them in a mergesort manner (see closest() below)
//
// Then we can use Floyd to compute the shortest distance from every
// elevator to every other elevator.
//
// For each floor that can be reached by elevators, from the elevators
// that stop at that floor we can figure out the cheapest way to reach
// that floor.  We also have to consider the top floor by riding each elevator
// to the top and walk the rest of the way.  Between every pair of consecutive
// reachable floors, we can work out the worst possible floor in between.
// Those are the only candidates.


using namespace std;

int closest(const vector<int> &v1, const vector<int> &v2)
{
  int n1 = v1.size(), n2 = v2.size();
  int ans = 2000000000;

  int i1 = 0, i2 = 0;
  while (i1 < n1 && i2 < n2) {
    if (v1[i1] == v2[i2]) return 0;
    else if (v1[i1] < v2[i2]) {
      ans = min(ans, v2[i2] - v1[i1]);
      i1++;
    } else {
      ans = min(ans, v1[i1] - v2[i2]);
      i2++;
    }
  }
  return ans;
}

typedef pair<int,int> pii;

void solve()
{
  int F, E;
  cin >> F >> E;

  int R[101], M[101];
  vector<int> stop[101];

  map<int, vector<int>> floors;  // floor -> elevator that stops there

  for (int i = 1; i <= E; i++) {
    cin >> R[i] >> M[i];
    for (int s = R[i]; s < F; s += M[i]) {
      stop[i].push_back(s);
      floors[s].push_back(i);
    }
  }


  int dist[101][101];    // 0 = ground, 1-E = elevator
  for (int i = 0; i < E+1; i++) {
    fill(dist[i], dist[i]+E+1, F+1);
  }

  dist[0][0] = 0;
  for (int i = 1; i <= E; i++) {
    dist[0][i] = dist[i][0] = R[i];
    dist[i][i] = 0;
    for (int j = i+1; j <= E; j++) {
      dist[i][j] = dist[j][i] = closest(stop[i], stop[j]);
    }
  }

  for (int k = 0; k < E+1; k++) {
    for (int i = 0; i < E+1; i++) {
      for (int j = 0; j < E+1; j++) {
	dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  pair<int,int> ans;    // -dist, floor

  int last_floor_dist = F-1;
  
  // the top floor: go to last stop and then walk
  for (int i = 1; i <= E; i++) {
    int last = stop[i][stop[i].size()-1];
    last_floor_dist = min(last_floor_dist, dist[0][i] + F-1-last);
  }
  ans = pii(-last_floor_dist, F-1);

  // now collect all the floors
  vector<pii> dist_floor;
  dist_floor.emplace_back(0,0);
  
  for (const auto &p : floors) {
    int f = p.first;

    if (!f) continue;                // don't worry about ground
    
    const vector<int> &v = p.second;
    int dist_to_floor = f;           // can always just walk
    for (auto x : v) {
      dist_to_floor = min(dist_to_floor, dist[0][x]);
    }
    dist_floor.emplace_back(f, dist_to_floor);
  }

  // now look at all the floors and those in between
  for (int i = 1; i < dist_floor.size(); i++) {
    int gap = dist_floor[i].first - dist_floor[i-1].first;

    // get to that floor
    ans = min(ans, pii(-dist_floor[i].second, dist_floor[i].first));


    // get to the one in between
    int worst = dist_floor[i-1].first +
      (-dist_floor[i-1].second + dist_floor[i].second + gap) / 2;

    int D = dist_floor[i-1].second + (worst - dist_floor[i-1].first);
    ans = min(ans, pii(-D, worst));
    
  }

  cout << -ans.first << ' ' << ans.second << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();

  return 0;
}
