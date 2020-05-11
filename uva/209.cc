/* @JUDGE_ID: 1102NT 209 C++ "" */

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

void coord(int p, int &r, int &c)
{
  int s = 1;

  for (r = 1; p >= s+r; r++) {
    s += r;
  }
  c = p-s;
}

bool triangle(int points[])
{
  int r[3], c[3], len;
  for (int i = 0; i < 3; i++) {
    coord(points[i], r[i], c[i]);
  }
  
  /* check upside down triangles */
  if (r[0] == r[1] && c[2] == c[1]) {
    len = c[1] - c[0];
    if (len == r[2] - r[1] && c[0] + len == c[2]) {
      return true;
    }
  }

  /* check rightside up triangles */
  if (r[1] == r[2] && c[0] == c[1]) {
    len = c[2] - c[1];
    if (len == r[1] - r[0] && c[0]+len == c[2]) {
      return true;
    }
  }
  return false;
}

bool parallelogram(int points[])
{
  int r[4], c[4], len;

  for (int i = 0; i < 4; i++) {
    coord(points[i], r[i], c[i]);
  }

  /* check vertical ones */
  if (r[0] < r[1] && r[1] == r[2] && r[2] < r[3]) {
    len = r[1] - r[0];
    if (len == r[3]-r[2] && c[1] == c[0] && c[2] == c[3] &&
	c[0]+len == c[2] && c[1]+len == c[3]) {
      return true;
    }
  }
  
  /* check horizontal ones */
  if (r[0] == r[1] && r[1] < r[2] && r[2] == r[3]) {
    len = r[2] - r[1];
    if (c[1]-c[0] == len && c[3]-c[2] == len) {
      if (c[0]+len == c[2] && c[1]+len == c[3] ||
	  c[0] == c[2] && c[1] == c[3]) {
	return true;
      }
    }
  }

  return false;
}

bool hexagon(int points[])
{
  int r[6], c[6], len;
  for (int i = 0; i < 6; i++) {
    coord(points[i], r[i], c[i]);
  }
  if (r[0] == r[1] && r[2] == r[3] && r[4] == r[5]) {
    len = c[1] - c[0];
    if (r[2]-r[1] == len && r[4]-r[3] == len && c[5]-c[4] == len &&
	c[0] == c[2] && c[1]+len == c[3] &&
	c[2]+len == c[4] && c[3] == c[5]) {
      return true;
    }
  }
  return false;
}

int main(void)
{
  string s;

  while (getline(cin, s)) {
    istringstream ss(s);
    int n = 0, t;
    int points[6];

    while (ss >> t) {
      points[n++] = t;
    }

    sort(points, points+n);

    cout << s << " are ";
    if (n == 3 && triangle(points)) {
      cout << "the vertices of a triangle" << endl;
    } else if (n == 4 && parallelogram(points)) {
      cout << "the vertices of a parallelogram" << endl;
    } else if (n == 6 && hexagon(points)) {
      cout << "the vertices of a hexagon" << endl;
    } else {
      cout << "not the vertices of an acceptable figure" << endl;
    }
  }
  return 0;
}
