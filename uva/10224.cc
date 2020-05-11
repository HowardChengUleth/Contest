//
// NOTE: this code is not accepted, even though I believe it is correct.
//       The accepted "solution" only considers going along the tangent
//       lines common to any pair of trees.  The correct solution should
//       actually consider going between all possible pairs of "interesting"
//       points.

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

const int MAX_TREES = 10 + 2;    // 2 for the start and end

// for each pair of nodes, there can be up to 8 points
const int MAX_NODES = MAX_TREES * (MAX_TREES-1)/2 * 8;

const double PI = acos(-1.0);

double graph[MAX_NODES][MAX_NODES];

struct Point {
  double x, y;

  Point(double xx = 0.0, double yy = 0.0) : x(xx), y(yy) { }
  Point(const Point &p1, const Point &p2)
    : x(p1.x - p2.x), y(p1.y - p2.y) { }
  Point(const Point &p1, double len)
    : x(p1.x), y(p1.y)
  {
    double d = norm();
    x *= len/d;
    y *= len/d;
  }
  
  double norm() const
  {
    return hypot(x, y);
  }
};

struct Tree {
  Point c;
  double r;
};

typedef pair<Point, int> PointInfo;

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y;
}

istream &operator>>(istream &is, Tree &t)
{
  is >> t.c >> t.r;
  t.r /= 2.0;
  return is;
}

int T;
Point start, end;
Tree tree[MAX_TREES];
vector<PointInfo> info;

double dist(const Point &p1, const Point &p2)
{
  return Point(p1, p2).norm();
}

double dist_to_line(const Point &p, const Point &a, const Point &b)
{
  Point u(p, a), v(b, a);
  double dot = (u.x * v.x + u.y * v.y) / (v.norm() * v.norm());

  if (0 <= dot && dot <= 1) {
    return sqrt(u.norm() * u.norm() - dot * v.norm() * dot * v.norm());
  } else {
    return min(dist(p, a), dist(p, b));
  }
}

// add an edge between the points in info[i] and info[j], provided that
// nothing is in the way
void add_edge(int i, int j)
{
  for (int k = 0; k < T; k++) {
    if (info[i].second == k || info[j].second == k) continue;
    if (dist_to_line(tree[k].c, info[i].first, info[j].first) < tree[k].r) {
      return;
    }
  }

  graph[i][j] = graph[j][i] = dist(info[i].first, info[j].first);
}

// rotate a vector (represented by a point) by theta counterclockwise
Point rotate(const Point &p, double theta)
{
  return Point(p.x * cos(theta) - p.y * sin(theta),
	       p.x * sin(theta) + p.y * cos(theta));
}

Point add(const Point &p1, const Point &p2)
{
  return Point(p1.x + p2.x, p1.y + p2.y);
}

// add edges from the point to tangent points of the tree
void process(const Point &p, int p_index, const Tree &t, int t_index)
{
  Point vec(t.c, p);
  double d = vec.norm();
  double theta = asin(t.r / d);
  vec = Point(vec, sqrt(d*d - t.r*t.r));
  Point dis1 = rotate(vec, theta),
    dis2 = rotate(vec, -theta);
  Point p1 = add(p, dis1), p2 = add(p, dis2);

  info.push_back(make_pair(p1, t_index));
//  add_edge(p_index, info.size()-1);
  
  info.push_back(make_pair(p2, t_index));
//  add_edge(p_index, info.size()-1);
}

// add edges from between tangent points of two trees
void process(const Tree &t1, int t1_index, const Tree &t2, int t2_index)
{
  if (t1.r > t2.r) {
    process(t2, t2_index, t1, t1_index);
    return;
  }

  // there are four possible tangent lines.  Two on the outside, and two
  // crossing into the middle

  //////////////////////////////////////////////////////////////////////
  //
  // first the ones on the outside: will have p1 to p2, p3 to p4.
  // p1, p3 are on the bigger circle (t2)
  // p2, p4 are on the smaller circle (t1)
  //
  //////////////////////////////////////////////////////////////////////

  Point vec(t2.c, t1.c);       // vector from one t1 to t2
  double vlen = vec.norm();

  // angle between vec and the line parallel to the tangent
  double theta = asin((t2.r - t1.r)/vlen);

  // length of tangent connecting the two points
  double tangent_len = vlen * cos(theta);

  // angle between tangents and t1's center to p1.
  double phi = atan(t1.r / tangent_len);

  // dist from t1's center to p1
  double dist_to_p1 = tangent_len / cos(phi);

  Point scaled_vec(vec, dist_to_p1);
  Point dis1 = rotate(scaled_vec, theta+phi),
    dis3 = rotate(scaled_vec, -theta-phi);
  Point p1 = add(t1.c, dis1), p3 = add(t1.c, dis3);

  scaled_vec = Point(vec, t1.r);
  Point dis2 = rotate(scaled_vec, theta + PI/2),
    dis4 = rotate(scaled_vec, -theta - PI/2);
  Point p2 = add(t1.c, dis2), p4 = add(t1.c, dis4);

//  int ind1 = info.size();
  info.push_back(make_pair(p1, t2_index));
//  int ind2 = info.size();
  info.push_back(make_pair(p2, t1_index));
//  int ind3 = info.size();
  info.push_back(make_pair(p3, t2_index));
//  int ind4 = info.size();
  info.push_back(make_pair(p4, t1_index));

//  add_edge(ind1, ind2);
//  add_edge(ind3, ind4);
    
  //////////////////////////////////////////////////////////////////////
  //
  // now the ones in the inside: will have p1 to p2, p3 to p4.
  // p1, p3 are on the bigger circle (t2)
  // p2, p4 are on the smaller circle (t1)
  //
  //////////////////////////////////////////////////////////////////////

  theta = asin((t1.r + t2.r) / vlen);
  tangent_len = vlen * cos(theta);
  phi = atan(t1.r / tangent_len);
  dist_to_p1 = tangent_len / cos(phi);

  scaled_vec = Point(vec, dist_to_p1);
  dis1 = rotate(scaled_vec, theta - phi);
  dis3 = rotate(scaled_vec, phi - theta);
  p1 = add(t1.c, dis1);
  p3 = add(t1.c, dis3);

  scaled_vec = Point(vec, t1.r);
  dis2 = rotate(scaled_vec, theta - PI/2);
  dis4 = rotate(scaled_vec, PI/2 - theta);
  p2 = add(t1.c, dis2);
  p4 = add(t1.c, dis4);

//  ind1 = info.size();
  info.push_back(make_pair(p1, t2_index));
//  ind2 = info.size();
  info.push_back(make_pair(p2, t1_index));
//  ind3 = info.size();
  info.push_back(make_pair(p3, t2_index));
//  ind4 = info.size();
  info.push_back(make_pair(p4, t1_index));

//  add_edge(ind1, ind2);
//  add_edge(ind3, ind4);
}

void do_case(void)
{
  cin >> T >> start >> end;
  for (int i = 0; i < T; i++) {
    cin >> tree[i];
  }

  info.clear();
  info.reserve(MAX_NODES);

  for (int i = 0; i < MAX_NODES; i++) {
    fill(graph[i], graph[i] + MAX_NODES, -1);
    graph[i][i] = 0;
  }
  
  // handle the start and end point with each tree
  info.push_back(make_pair(start, -1));
  info.push_back(make_pair(end, -2));
  add_edge(0, 1);
  
  for (int i = 0; i < T; i++) {
    process(start, 0, tree[i], i);
    process(end, 1, tree[i], i);
  }

  // now do all possible pairs of trees
  for (int i = 0; i < T; i++) {
    for (int j = i+1; j < T; j++) {
      process(tree[i], i, tree[j], j);
    }
  }

  // now go through all points and link up all points from the same tree
  for (unsigned int i = 0; i < info.size(); i++) {
    for (unsigned int j = i+1; j < info.size(); j++) {
       if (info[i].second == info[j].second) {
	  const Tree &t = tree[info[i].second];
	  double theta = 2*asin((dist(info[i].first, info[j].first)/2) / t.r);
	  graph[i][j] = graph[j][i] = theta*t.r;
       } else {
	  // remove this statement to make it accepted
	  add_edge(i, j);
       }
    }
  }

/*
  cout << "info.size() = " << info.size() << endl;

  cout << "************************************" << endl;
  for (int i = 0; i < info.size(); i++) {
    for (int j = 0; j < info.size(); j++) {
      cout << fixed << setprecision(2) << setw(5) << graph[i][j] << ' ';
    }
    cout << endl;
  }
  cout << "************************************" << endl;
*/

  // run floyd's
  for (unsigned int k = 0; k < info.size(); k++) {
    for (unsigned int i = 0; i < info.size(); i++) {
      for (unsigned int j = 0; j < info.size(); j++) {
	if (graph[i][k] != -1 && graph[k][j] != -1) {
	  double t = graph[i][k] + graph[k][j];
	  if (graph[i][j] == -1 || t < graph[i][j]) {
	    graph[i][j] = t;
	  }
	}
      }
    }
  }

  /*
  cout << "************************************" << endl;
  for (int i = 0; i < info.size(); i++) {
    for (int j = 0; j < info.size(); j++) {
      cout << fixed << setprecision(2) << setw(5) << graph[i][j] << ' ';
    }
    cout << endl;
  }
  cout << "************************************" << endl;
  */

  cout << fixed << setprecision(2) << graph[0][1]/(200.0/3600) << endl;
}

int main(void)
{
  int N;
  cin >> N;

  while (N-- > 0) {
    do_case();

    if (N) {
      cout << endl;
    }
  }
  
  return 0;
}
