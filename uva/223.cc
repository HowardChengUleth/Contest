#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>
#include <numeric>
#include <cassert>

using namespace std;

const double PI = acos(-1.0);

struct Point : public pair<int, int>
{
  explicit Point(int x = 0, int y = 0)
  {
    first = x;
    second = y;
  }
  
  int &x() { return first; }
  const int &x() const { return first; }
  int &y() { return second; }
  const int &y() const { return second; }
};

typedef pair<Point, Point> Line;

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x() >> p.y();
}

ostream &operator<<(ostream &os, const Point &p)
{
  return os << p.x() << ' ' << p.y();
}

istream &operator>>(istream &is, Line &l)
{
  return is >> l.first >> l.second;
}

void insert_point(map<Point, unsigned int> &pointmap, const Point &p)
{
  if (pointmap.find(p) == pointmap.end()) {
    unsigned int index = pointmap.size();
    pointmap[p] = index;
  }
}

int N;
vector<Point> points;
Line line[200];

int find_lower_left(const vector<Point> &points,
		    const vector< vector<int> > &adj_list)
{
  int ans = -1;
  
  for (unsigned int i = 0; i < points.size(); i++) {
    if (adj_list[i].size() == 0) continue;
    if (ans == -1 || points[i].y() < points[ans].y() ||
	(points[i].y() == points[ans].y() &&
	 points[i].x() < points[ans].x())) {
      ans = i;
    }
  }
  return ans;
}

void mark_edge(int u, int v, vector< vector<int> > &adj_list, int canuse[])
{
  for (int i = 0; i < N; i++) {
    if ((line[i].first == points[u] && line[i].second == points[v]) ||
	(line[i].first == points[v] && line[i].second == points[u])) {
      // found the edge
      assert(canuse[i] > 0);
      canuse[i]--;
      if (canuse[i] > 0) return;

      // need to remove that edge
      remove(adj_list[u].begin(), adj_list[u].end(), v);
      adj_list[u].pop_back();
      remove(adj_list[v].begin(), adj_list[v].end(), u);
      adj_list[v].pop_back();
      return;
    }
  }
  assert(false);
}

// angle of p1 -> p2 and positive x-axis
double angle(const Point &p1, const Point &p2)
{
  double y = p2.y() - p1.y();
  double x = p2.x() - p1.x();
  double ang = atan2(y,x);
  if (ang < 0) ang += 2*PI;
  return ang;
}

// just arrived at v, the last edge has angle ang_in, wanting to get to u
int trace(int v, int u, vector< vector<int> > &adj_list, int canuse[],
	  double ang_in)
{
  // first, see if we can get back to u
  if (find(adj_list[v].begin(), adj_list[v].end(), u) != adj_list[v].end()) {
    mark_edge(v, u, adj_list, canuse);
    return 1;
  }

  // now choose the edge that has the largest CCW turn (up to 180 degrees)
  double best_ang;
  int best_w = -1;
  for (unsigned int i = 0; i < adj_list[v].size(); i++) {
    int w = adj_list[v][i];
    double ang_out = angle(points[v], points[w]);
    double diff = ang_out - ang_in;
    if (diff > PI) diff -= 2*PI;
    if (diff < -PI) diff += 2*PI;
    //    cout << "    " << points[v] << " => " << points[w] << ": diff = " << diff << endl;

    if (fabs(diff - PI) < 1e-6) continue;
    if (best_w == -1 || diff > best_ang) {
      best_w = w;
      best_ang = diff;
    }
  }
  
  //  cout << "  picked the edge " << points[v] << " => "
  //       << points[best_w] << endl;
  mark_edge(v, best_w, adj_list, canuse);
  return 1 + trace(best_w, u, adj_list, canuse,
		   angle(points[v], points[best_w]));
  
}

int starttrace(int u, vector< vector<int> > &adj_list, int canuse[])
{
  // pick the edge from u with the smallest angle
  double best_ang;
  int best_v = -1;
  for (unsigned int i = 0; i < adj_list[u].size(); i++) {
    int v = adj_list[u][i];
    double ang = angle(points[u], points[v]);
    if (best_v == -1 || ang < best_ang) {
      best_v = v;
      best_ang = ang;
    }
  }
  
  //  cout << "  picked the edge " << points[u] << " => "
  //       << points[best_v] << endl;

  mark_edge(u, best_v, adj_list, canuse);
  double ang = angle(points[u], points[best_v]);

  return 1 + trace(best_v, u, adj_list, canuse, ang);
}

void solve()
{
  map<Point, unsigned int> pointmap;
  for (int i = 0; i < N; i++) {
    cin >> line[i];
    insert_point(pointmap, line[i].first);
    insert_point(pointmap, line[i].second);
  }
  
  // now construct a list of points
  points.resize(pointmap.size());
  for (map<Point, unsigned int>::const_iterator it = pointmap.begin();
       it != pointmap.end(); ++it) {
    points[it->second] = it->first;
  }

  // now construct a graph
  vector< vector<int> > adj_list(pointmap.size());
  for (int i = 0; i < N; i++) {
    const Point &from = line[i].first;
    const Point &to = line[i].second;

    adj_list[pointmap[from]].push_back(pointmap[to]);
    adj_list[pointmap[to]].push_back(pointmap[from]);
  }

  // each line can be used twice unless it is on the boundary
  int canuse[200]; 
  int minx = pointmap.begin()->first.x();
  int miny = pointmap.begin()->first.y();
  int maxx = pointmap.rbegin()->first.x();
  int maxy = pointmap.rbegin()->first.y();
  for (int i = 0; i < N; i++) {
    if ((line[i].first.x() == line[i].second.x() &&
	 (line[i].first.x() == minx || line[i].first.x() == maxx)) ||
	(line[i].first.y() == line[i].second.y() &&
	 (line[i].first.y() == miny || line[i].first.y() == maxy))) {
      canuse[i] = 1;
    } else {
      canuse[i] = 2;
    }
  }

  int lots[201];
  fill(lots, lots+201, 0);
  int u;
  while ((u = find_lower_left(points, adj_list)) != -1) {
    //    cout << "Choosing starting point " << points[u] << endl;

    int len = starttrace(u, adj_list, canuse);
    lots[len]++;
  }

  int total = accumulate(lots, lots+201, 0);
  for (int i = 1; i <= 200; i++) {
    if (lots[i] > 0) {
      cout << "Number of lots with perimeter consisting of " << i
	   << " surveyor's lines = " << lots[i] << endl;
    }
  }
  cout << "Total number of lots = " << total << endl;
  
}

int main()
{
  int case_num = 1;
  while (cin >> N && N != 0) {
    if (case_num > 1) {
      cout << endl;
    }
    cout << "Case " << case_num++ << endl;
    solve();
  }
  return 0;
}
