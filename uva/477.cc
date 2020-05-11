#include <iostream>
#include <algorithm>

using namespace std;

class Shape {
public:
  virtual bool inside(double x, double y) = 0;
};

class Rectangle : public Shape {
protected:
  double x1, x2, y1, y2;
public:
  Rectangle(double ulx, double uly, double lrx, double lry)
    : x1(ulx), x2(lrx), y1(lry), y2(uly)
  {
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
  }

  bool inside(double x, double y)
  {
    return (x1 < x && x < x2 && y1 < y && y < y2);
  }
};

class Circle : public Shape {
protected:
  double cx, cy, r;
public:
  Circle(double x, double y, double rad)
    : cx(x), cy(y), r(rad)
  {
  }

  bool inside(double x, double y)
  {
    return (x-cx)*(x-cx) + (y-cy)*(y-cy) < r*r;
  }
};
  
int main(void)
{
  Shape *figs[10];
  int num_figs = 0;

  char c;

  while (cin >> c && c != '*') {
    if (c == 'r') {
      double ulx, uly, lrx, lry;
      cin >> ulx >> uly >> lrx >> lry;
      figs[num_figs++] = new Rectangle(ulx, uly, lrx, lry);
    } else {
      double x, y, rad;
      cin >> x >> y >> rad;
      figs[num_figs++] = new Circle(x, y, rad);
    }
  }

  double x, y;
  int point_num = 0;
  while (cin >> x >> y && !(x == 9999.9 && y == 9999.9)) {
    point_num++;
    bool found = false;
    for (int i = 0; i < num_figs; i++) {
      if (figs[i]->inside(x, y)) {
	cout << "Point " << point_num << " is contained in figure "
	     << i+1 << endl;
	found = true;
      }
    }
    if (!found) {
      cout << "Point " << point_num << " is not contained in any figure"
	   << endl;
    }
  }

  return 0;
}
