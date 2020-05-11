//Problem 361
//Written by Nathan House
//Started 1:21 Oct 24.
//Total time: 25mins

#include<iostream>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include<cassert>
#include<string>
#include<vector>

using namespace std;

struct Point{
  int x,y;
  bool operator<(const Point &p) const {
    return y < p.y || (y == p.y && x < p.x);
  }
};

int numCit,numCop,numRob;
Point cits[200];
Point robs[200];
Point cops[200];

const double EPSILON = 1E-8;
const bool BOUNDARY = true;
enum Orientation {CCW, CW, CNEITHER};
//Function headers
Orientation ccw(Point, Point, Point);
bool ccw_cmp(const Point &a, const Point &b);
int convex_hull(Point polygon[], int n, Point hull[]);
bool point_in_poly(Point poly[], int n, Point p);


int main()
{
   int copHullsize=0;
   int robHullsize=0;
   Point copHull[200];
   Point robHull[200];
   int cases = 0;
   
   while(true)
   {
      cin >> numCop >> numRob >> numCit;
      if(numCop==0 && numRob==0 && numCit==0)
	 break;
      for(int i=0; i<numCop; i++)
	 cin >> cops[i].x >> cops[i].y;
      for(int i=0; i<numRob; i++)
	 cin >> robs[i].x >> robs[i].y;
      for(int i=0; i<numCit; i++)
	 cin >> cits[i].x >> cits[i].y;

      cout << "Data set " << cases+1 << ":" << endl;
      copHullsize=convex_hull(cops, numCop, copHull);
      robHullsize=convex_hull(robs, numRob, robHull);
      for(int j=0; j<numCit; j++)
      {
	 cout << "     Citizen at (" << cits[j].x << ","
	      << cits[j].y << ") is ";
	 if(point_in_poly(copHull, copHullsize, cits[j]))
	    cout << "safe." << endl;
	 else
	 {
	    if(point_in_poly(robHull, robHullsize, cits[j]))
	       cout << "robbed." << endl;
	    else
	    {
	       cout << "neither." << endl;
	    }
	 }
      }
      cout << endl;
      cases++;
   }
   return 0;
}

//CODE FROM LIBRARY
/* Global point for computing convex hull */
Point start_p, max_p; 

bool colinear(Point a, Point b, Point c)
{
  long long dx1 = b.x - a.x;
  long long dx2 = c.x - b.x;
  long long dy1 = b.y - a.y;
  long long dy2 = c.y - b.y;
  long long t1 = dy2 * dx1;
  long long t2 = dy1 * dx2;
  return t1 == t2;
}

Orientation ccw(Point a, Point b, Point c)
{
  long long dx1 = b.x - a.x;
  long long dx2 = c.x - b.x;
  long long dy1 = b.y - a.y;
  long long dy2 = c.y - b.y;
  long long t1 = dy2 * dx1;
  long long t2 = dy1 * dx2;

  if (t1 == t2) {
    if (dx1 * dx2 < 0 || dy1 * dy2 < 0) {
      if (dx1*dx1 + dy1*dy1 >= dx2*dx2 + dy2*dy2) {
        return CNEITHER;
      } else {
        return CW;
      }
    } else {
      return CCW;
    }
  } else if (t1 > t2) {
    return CCW;
  } else {
    return CW;
  }
}

bool ccw_cmp(const Point &a, const Point &b)
{
  return ccw(start_p, a, b) == CCW;
}

bool sort_cmp(const Point &a, const Point &b)
{
  if (colinear(start_p, a, max_p) && colinear(start_p, b, max_p)) {
    long long dx1 = abs(start_p.x - a.x);
    long long dx2 = abs(start_p.x - b.x);
    long long dy1 = abs(start_p.y - a.y);
    long long dy2 = abs(start_p.y - b.y);
    return dx1 > dx2 || (dx1 == dx2 && dy1 > dy2);
  } else {
    return ccw(start_p, a, b) == CCW;
  }
}

int convex_hull(Point polygon[], int n, Point hull[]) {
  int count, best_i, i;

  if (n == 1) {
    hull[0] = polygon[0];
    return 1;
  }
  if (n == 0) {
    return 0;
  }
  
  sort(polygon, polygon+n);
  for (int i = n-1; i >= 1; i--) {
    if (polygon[i].x == polygon[i-1].x &&
	polygon[i].y == polygon[i-1].y) {
      for (int j = i; j < n-1; j++) {
	polygon[j] = polygon[j+1];
      }
      n--;
    }
  }

  if (n == 1) {
    hull[0] = polygon[0];
    return 1;
  }

  /* find the first point: min y, and then min x */
  best_i = min_element(polygon, polygon+n) - polygon;
  swap(polygon[0], polygon[best_i]);
  start_p = polygon[0];

  /* find the maximum angle wrt start_p and positive x-axis */
  best_i = 1;
  for (i = 2; i < n; i++) {
    if (ccw_cmp(polygon[best_i], polygon[i])) {
      best_i = i;
    }
  }
  max_p = polygon[best_i];

  /* get simple closed polygon */
  sort(polygon+1, polygon+n, sort_cmp);

  /* do convex hull */
  count = 0;
  hull[count] = polygon[count]; count++;
  hull[count] = polygon[count]; count++;
  for (i = 2; i < n; i++) {
    while (count > 1 &&
           ccw(hull[count-2], hull[count-1], polygon[i]) == CW) {
      /* pop point */
      count--;
    }
    hull[count++] = polygon[i];
  }
  return count;
}


bool point_in_poly(Point poly[], int n, Point p)
{
   int i, j, c = 0;

   if (n <= 2) {
     return false;
   }

   /* first check to see if point is one of the vertices */
   for (i = 0; i < n; i++) {
      if (p.x == poly[i].x && p.y == poly[i].y) {
	 return BOUNDARY;
      }
   }

   /* now check if it's on the boundary */
   for (i = 0; i < n-1; i++) {
      if (ccw(poly[i], poly[i+1], p) == CNEITHER) {
	 return BOUNDARY;
      }
   }
   if (ccw(poly[n-1], poly[0], p) == CNEITHER) {
      return BOUNDARY;
   }

   /* finally check if it's inside */
   for (i = 0, j = n-1; i < n; j = i++) {
      if (((poly[i].y <= p.y && p.y < poly[j].y) ||
	   (poly[j].y <= p.y && p.y < poly[i].y)) &&
	  (p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y)
	   / (poly[j].y - poly[i].y) + poly[i].x))
	 c = !c;
   }
   return c;
}
