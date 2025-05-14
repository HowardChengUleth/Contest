#include <bits/stdc++.h>

using namespace std;

class Shape
{
public:
  virtual bool hit(int x, int y) = 0;
  virtual void read() = 0;
};

class Rectangle : public Shape
{
public:
  virtual bool hit(int x, int y)
  {
    return x1 <= x && x <= x2 && y1 <= y && y <= y2;
  }

  virtual void read()
  {
    cin >> x1 >> y1 >> x2 >> y2;
  }
  
private:
  int x1, y1, x2, y2;
};

class Circle : public Shape
{
public:
  virtual bool hit(int x, int y)
  {
    int dx = x - cx, dy = y - cy;
    return dx*dx + dy*dy <= r*r;
  }

  virtual void read()
  {
    cin >> cx >> cy >> r;
  }
  
private:
  int cx, cy, r;
};


int main()
{
  int m;
  cin >> m;

  vector<Shape *> shapes;
  for (int i = 0; i < m; i++) {
    string type;
    cin >> type;

    Shape *s;
    if (type == "rectangle") {
      s = new Rectangle;
    } else {
      s = new Circle;
    }
    s->read();
    shapes.push_back(s);
  }

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x, y, count = 0;
    cin >> x >> y;
    for (int j = 0; j < m; j++) {
      if (shapes[j]->hit(x, y)) {
	count++;
      }
    }
    cout << count << endl;
  }

  return 0;
}
