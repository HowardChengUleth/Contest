#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<int> vi;

#define INF 1000000000
#define sz(x) (int)(x).size()
#define debug(a) cerr << #a << " = " << (a) << endl;

template<typename T, typename U> ostream& operator<<(ostream& o, const pair<T, U>& x) { o << "(" << x.first << ", " << x.second << ")"; return o; }
template<typename T> ostream& operator<<(ostream& o, const vector<T>& x) { o << "["; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "]"; return o; }
template<typename T> ostream& operator<<(ostream& o, const set<T>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T> ostream& operator<<(ostream& o, const multiset<T>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T> ostream& operator<<(ostream& o, const unordered_set<T>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T> ostream& operator<<(ostream& o, const unordered_multiset<T>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T, typename U> ostream& operator<<(ostream& o, const map<T, U>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T, typename U> ostream& operator<<(ostream& o, const multimap<T, U>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T, typename U> ostream& operator<<(ostream& o, const unordered_map<T, U>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T, typename U> ostream& operator<<(ostream& o, const unordered_multimap<T, U>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }

const double EPSILON = 1E-8;

struct Point {
  double x, y;
};

/* returns 1 if intersect at a point, 0 if not, -1 if the lines coincide */
int intersect_iline(Point a, Point b, Point c, Point d, Point &p)
{
  double r;
  double denom, num1, num2;

  assert((a.x != b.x || a.y != b.y) && (c.x != d.x || c.y != d.y));

  num1 = (a.y - c.y)*(d.x - c.x) - (a.x - c.x)*(d.y - c.y);
  num2 = (a.y - c.y)*(b.x - a.x) - (a.x - c.x)*(b.y - a.y);
  denom = (b.x - a.x)*(d.y - c.y) - (b.y - a.y)*(d.x - c.x);

  if (fabs(denom) >= EPSILON) {
    r = num1 / denom;
    p.x = a.x + r*(b.x - a.x);
    p.y = a.y + r*(b.y - a.y);
    return 1;
  } else {
    if (fabs(num1) >= EPSILON) {
      return 0;
    } else {
      return -1;
    }
  }
}

/* computes the distance from "c" to the line defined by "a" and "b" */
double dist_line(Point a, Point b, Point c)
{
  double L2, s;

  L2 = (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
  assert(L2 > 0);
  s = ((a.y-c.y)*(b.x-a.x)-(a.x-c.x)*(b.y-a.y)) / L2;

  return fabs(s*sqrt(L2));
}

bool between(Point a, Point b, Point c)
{
  double x1 = min(a.x, b.x), x2 = max(a.x, b.x);
  double y1 = min(a.y, b.y), y2 = max(a.y, b.y);

  return x1 <= c.x && c.x <= x2 && y1 <= c.y && c.y <= y2;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int S; cin>>S;
    vector<pair<Point, Point>> streets(S);
    for(int i=0; i<S; i++)
        cin>>streets[i].first.x>>streets[i].first.y>>streets[i].second.x>>streets[i].second.y;

    int T; cin>>T;
    for(int i=0; i<T; i++) {
        Point a,b,p;
        cin>>a.x>>a.y>>b.x>>b.y;

        int count = 0;
        for(auto s:streets) {
      if(intersect_iline(a,b,s.first,s.second,p) == 1 && between(a, b, p))
                count++;
        }

        if(count%2)
            cout<<"different"<<endl;
        else
            cout<<"same"<<endl;
    }
}
