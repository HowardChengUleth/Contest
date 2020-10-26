#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, s;

struct Data {
  ll x, y;
  long double index;

  long double compute(long double xx, long double yy, long double ss, int level = 0)
  {
    //    cout << "ss = " << ss << endl;
    if (level > 30) {
      return 0;
    }

    long double midpoint = ss/2.0;
    long double quad_size = midpoint*midpoint;
		    
    int quad_index;
    long double x2 = xx, y2 = yy;
    
    if (xx < midpoint && yy < midpoint) {
      quad_index = 1;
      swap(x2, y2);
    } else if (xx < midpoint && yy >= midpoint) {
      y2 -= midpoint;
      quad_index = 2;
    } else if (xx >= midpoint && yy >= midpoint) {
      x2 -= midpoint;
      y2 -= midpoint;
      quad_index = 3;
    } else {
      quad_index = 4;
      x2 -= midpoint;
      swap(x2, y2);
      x2 = midpoint - x2;
      y2 = midpoint - y2;
    }

    long double before = (quad_index-1)*quad_size;
    return before + compute(x2, y2, ss/2, level+1);
  }
  
  void read()
  {
    cin >> x >> y;
    index = compute(x, y, s);
  }

  void print() const
  {
    cout << x << ' ' << y << endl;
  }

  bool operator<(const Data &d) const
  {
    return index < d.index;
  }
};

Data A[100000];

int main()
{
  cin >> n >> s;
  for (int i = 0; i < n; i++) {
    A[i].read();
  }
  
  sort(A, A+n);

  for (int i = 0; i < n; i++) {
    A[i].print();
  }
  

  return 0;
}
