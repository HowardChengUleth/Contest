#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

struct Point {
  int x, y;
  
  Point(int i, int j) : x(i), y(j) { }
  int dist(const Point &p) const {
    return abs(x - p.x) + abs(y - p.y);
  }
};

int main(void)
{
  int M;

  while (cin >> M) {
    vector<Point> v1, v3;
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < M; j++) {
	char ch;
	cin >> ch;
	if (ch == '1') {
	  v1.push_back(Point(i,j));
	} else if (ch == '3') {
	  v3.push_back(Point(i,j));
	}
      }
    }

    int best = INT_MIN;
    for (int i = 0; i < v1.size(); i++) {
      int d = INT_MAX;
      for (int j = 0; j < v3.size(); j++) {
	int t = v1[i].dist(v3[j]);
	if (t < d) {
	  d = t;
	}
      }
      if (d > best) {
	best = d;
      }
    }
    cout << best << endl;

  }
  return 0;
}
