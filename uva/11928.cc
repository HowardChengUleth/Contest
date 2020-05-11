// Idea: 
//
// First translate the coordinates so that the post is at the origin.
//
// We just count the number of times the polygon crosses the positive
// x-axis.  If it crosses counterclockwise, we add +1.  If it crosses
// clockwise, we add -1.  That is the answer assuming we have not run into
// the post.

#include <iostream>
#include <cmath>

using namespace std;

struct Point {
  int x, y;
};

int direction(Point p1, Point p2, Point p3)
{
  int x1 = p3.x - p1.x;
  int y1 = p3.y - p1.y;
  int x2 = p2.x - p1.x;
  int y2 = p2.y - p1.y;
  return x1*y2 - x2*y1;
}

int on_segment(Point p1, Point p2, Point p3)
{
  return ((p1.x <= p3.x && p3.x <= p2.x) || (p2.x <= p3.x && p3.x <= p1.x)) &&
    ((p1.y <= p3.y && p3.y <= p2.y) || (p2.y <= p3.y && p3.y <= p1.y));
}

int intersect(Point a1, Point a2, Point b1, Point b2)
{
  int d1 = direction(b1, b2, a1);
  int d2 = direction(b1, b2, a2);
  int d3 = direction(a1, a2, b1);
  int d4 = direction(a1, a2, b2);

  if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
      ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
    return 1;
  } else {
    return (d1 == 0 && on_segment(b1, b2, a1)) ||
      (d2 == 0 && on_segment(b1, b2, a2)) ||
      (d3 == 0 && on_segment(a1, a2, b1)) ||
      (d4 == 0 && on_segment(a1, a2, b2));
  }
}

bool do_case()
{
  int n;
  cin >> n;
  if (!n) return false;

  Point pole;
  cin >> pole.x >> pole.y;
  
  Point polygon[10000];
  for (int i = 0; i < n; i++) {
    cin >> polygon[i].x >> polygon[i].y;
    
    // translate to pole = (0,0)
    polygon[i].x -= pole.x;
    polygon[i].y -= pole.y;
  }

  // positive x-axis
  Point p1, p2;
  p1.x = p1.y = p2.y = 0;
  p2.x = 20000;
  
  int wind = 0;
  for (int i = 0; i < n; i++) {
    int next = (i+1) % n;

    // check for hitting the post
    if (direction(polygon[i], polygon[next], p1) == 0 &&
	on_segment(polygon[i], polygon[next], p1)) {
      cout << "Ouch!" << endl;
      return true;
    }
    
    // doesn't intersect positive x-axis, nothing to do
    if (!intersect(p1, p2, polygon[i], polygon[next])) continue;

    // coincide with positive x-axis so it doesn't actually cross
    if (polygon[i].y == 0 && polygon[next].y == 0) continue;

    // if one of the endpoints is on the positive x-axis, then we
    // count that as "half": we are not quite crossing yet.  If we
    // complete the crossing the two halves from consecutive edges
    // will add up to 1.  If we bounce off and not really cross, then
    // the two halves will have opposite signs and cancel each other out.
    //
    // we store the 2*count instead of count so we don't have to deal with
    // floating-point numbers
    if (polygon[i].y == 0) {
      wind += (polygon[next].y > 0) ? 1 : -1;
    } else if (polygon[next].y == 0) {
      wind += (polygon[i].y < 0) ? 1 : -1;
    } else {
      // normal crossing, count as 2
      wind += 2*((polygon[next].y > polygon[i].y) ? 1 : -1);
    }
  }

  if (wind > 0) cout << "+";
  cout << wind/2 << endl;
  return true;
}

int main(void)
{
  while (do_case())
    ;

  return 0;
}
