/* @JUDGE_ID: 1102NT 10671 C++ "" */
#include <iostream>
#include <iomanip>
#include <map>
#include <cstdlib>

using namespace std;

const int MAX_STREET = 10;

struct ltint {
  inline bool operator()(int a, int b)
  {
    return (a < b);
  }
};

int n, gridsize, hv[MAX_STREET], vv[MAX_STREET];
int xs, ys, xt, yt, tmin, tmax;
int maxvv, maxhv;

double mpg(double v)
{
  return 80 - 0.03 * v * v;
}

void read_case(void)
{
  maxvv = maxhv = 0;
  cin >> n >> gridsize;

  for (int i = 0; i < n; i++) {
    cin >> hv[i];
    hv[i] /= 5;
    if (maxhv < hv[i]) {
      maxhv = hv[i];
    }
  }
  for (int i = 0; i < n; i++) {
    cin >> vv[i];
    vv[i] /= 5;
    if (maxvv < vv[i]) {
      maxvv = vv[i];
    }
  }
  cin >> xs >> ys >> xt >> yt >> tmin >> tmax;
  xs--; ys--; xt--; yt--;
  tmin *= 60; tmax *= 60;
}

int times[11];
double fuel[11];

void build_tables(void)
{
  for (int v = 5; v <= 50; v += 5) {
    times[v/5] = gridsize * 3600 / v;
    fuel[v/5] = gridsize / mpg(v);
  }
}

void solve_case(void)
{
  int dx, dy;

  build_tables();

  // figure out how to get from s to t
  dx = (xs <= xt) ? 1 : -1;
  dy = (ys <= yt) ? 1 : -1;

  map<int,double,ltint> path[MAX_STREET][MAX_STREET];
  map<int,double,ltint>::iterator p;

  path[xs][ys][0] = 0.0;
  for (int x = xs; x != xt + dx; x += dx) {
    for (int y = ys; y != yt + dy; y += dy) {
      if (x == xt && y == yt) break;

      int hdist = abs(xt-x);
      int vdist = abs(yt-y);
      int fast = hdist*times[maxhv] + vdist*times[maxvv];
      int slow = (hdist+vdist)*times[1];
      int fasth = tmax - (hdist-1)*times[maxhv] + vdist*times[maxvv];
      int fastv = tmax - (vdist-1)*times[maxvv] + hdist*times[maxhv];
      for (p = path[x][y].begin(); p != path[x][y].end(); ++p) {
	int time1 = p->first;

	// no matter how slow we go, we arrive too early
	if (time1 + slow < tmin) continue;

	// no matter how fast we go, we arrive too late
	if (time1 + fast > tmax) break;

	if (x != xt) {
	  for (int v = 1; v <= hv[y]; v++) {
	    int new_time = time1 + times[v];
	    if (new_time > fasth) continue;
	    double new_fuel = p->second + fuel[v];
	    double &loc = path[x+dx][y][new_time];
	    if (loc == 0.0 || new_fuel < loc) {
	      loc = new_fuel;
	    }
	  }
	}

	if (y != yt) {
	  for (int v = 1; v <= vv[x]; v++) {
	    int new_time = time1 + times[v];
	    if (new_time > fastv) continue;
	    double new_fuel = p->second + fuel[v];
	    double &loc = path[x][y+dy][new_time];
	    if (loc == 0.0 || new_fuel < loc) {
	      loc = new_fuel;
	    }
	  }
	}
      }
      path[x][y].clear();
    }
  }

  int earliest_time = -1, cheapest_time = -1;
  double earliest_fuel = -1, cheapest_fuel = -1;
  for (p = path[xt][yt].begin(); p != path[xt][yt].end(); ++p) {
    if (tmin <= p->first && p->first <= tmax) {
      if (earliest_time < 0 || p->first < earliest_time) {
	earliest_time = p->first;
	earliest_fuel = p->second;
      }
      if (cheapest_fuel < 0 || p->second < cheapest_fuel) {
	cheapest_time = p->first;
	cheapest_fuel = p->second;
      }
    }
  }

  if (earliest_time < 0) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    if (earliest_time % 60) {
      earliest_time = earliest_time / 60 + 1;
    } else {
      earliest_time = earliest_time / 60;
    }
    if (cheapest_time % 60) {
      cheapest_time = cheapest_time / 60 + 1;
    } else {
      cheapest_time = cheapest_time / 60;
    }
    cout.setf(ios::fixed);
    cout << "The earliest  arrival: " << earliest_time << " minutes, fuel ";
    cout.precision(2);
    cout << earliest_fuel << " gallons" << endl;
    cout.precision(0);
    cout << "The economical travel: " << cheapest_time << " minutes, fuel ";
    cout.precision(2);
    cout << cheapest_fuel << " gallons" << endl;
    cout.precision(0);
  }
}

int main(void)
{
  int t;

  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Scenario " << i << ":" << endl;
    read_case();
    solve_case();
  }
  return 0;
}
