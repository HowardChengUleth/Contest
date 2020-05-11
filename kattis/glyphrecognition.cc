#include <bits/stdc++.h>
using namespace std;
 
#define debug(a) cerr << #a << " = " << (a) << endl;

#define fst first
#define snd second

#define double long double

#define M_PI acos(-1)
 
template<typename T> ostream& operator<<(ostream& o, const vector<T>& v) {
	int b = 0; for (const auto& a : v) o << (b++ ? ", " : "") << a; return o;
}

template<typename T> ostream& operator<<(ostream& o, const set<T>& v) {
	int b = 0; for (const auto& a : v) o << (b++ ? ", " : "") << a; return o;
}
 
template<typename T, typename U> ostream& operator<<(ostream& o, const pair<T, U>& p) {
	o << p.fst << ' ' << p.snd; return o;
}

const double EPS = 1e-10;
bool dEqual(double x, double y) { return fabs(x-y) < EPS; }

struct Point {
    double x, y;
    Point() : x{0}, y{0} {}
    Point(double x_, double y_) : x{x_}, y{y_} {}
    bool operator==(const Point &p) const { return dEqual(x, p.x) && dEqual(y, p.y); }
    bool operator<(const Point &p) const { return y < p.y || (y == p.y && x < p.x); }
};

ostream& operator<<(ostream& o, const Point &p) {
    o << '(' << p.x << ',' << p.y << ')';
    return o;
}

Point operator-(Point p, Point q) { p.x -= q.x; p.y -= q.y; return p; }
Point operator+(Point p, Point q) { p.x += q.x; p.y += q.y; return p; }
Point operator*(double r, Point p) { p.x *= r; p.y *= r; return p; }
double operator*(Point p, Point q) { return p.x*q.x + p.y*q.y; }
double len(Point p) { return sqrt(p*p); }
double cross(Point p, Point q){ return p.x*q.y - q.x*p.y; }
Point inv(Point p){ Point q = {-p.y,p.x}; return q; }

enum Orientation {CCW, CW, CNEITHER};

Orientation ccw(Point a, Point b, Point c) {
    Point d1 = b - a, d2 = c - b;
    if (dEqual(cross(d1, d2), 0))
        if (d1.x * d2.x < 0 || d1.y * d2.y < 0)
            return (d1*d1 >= d2*d2 - EPS) ? CNEITHER : CW;
        else return CCW;
    else return (cross(d1, d2) > 0) ? CCW : CW;
}

double area_polygon(Point p[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += cross(p[i], p[(i+1)%n]);
    return sum/2.0;
}

int intersect_line(Point a, Point b, Point c, Point d, Point &p, bool segment) {
    double num1 = cross(d-c, a-c), num2 = cross(b-a, a-c), denom = cross(b-a, d-c);
    if (!dEqual(denom, 0)) {
        double r = num1 / denom, s = num2 / denom;
        if (!segment || (0 - EPS <= r && r <= 1+EPS && 0-EPS <= s && s <= 1+EPS)) {
            p = a + r*(b-a); return 1;
        } else return 0;
    }
    if (!segment) return dEqual(num1, 0) ? -1: 0;
    if (!dEqual(num1, 0)) return 0;
    if (b < a) swap(a, b);
    if (d < c) swap(c, d);
    if (a.x == b.x) {
        if (b.y == c.y) { p = b; return 1; }
        if (a.y == d.y) { p = a; return 1; }
        return (b.y < c.y || d.y < a.y) ? 0: -1;
    } else if (b.x == c.x) { p = b; return 1; }
    else if (a.x == d.x) { p = a; return 1; }
    else if (b.x < c.x || d.x < a.x) return 0;
    return -1;
}

const bool BOUNDARY = true;
bool point_in_poly(Point poly[], int n, Point p) {
    int i, j , c = 0;
    for (i = 0; i < n; i++) 
        if (poly[i] == p || ccw(poly[i], poly[(i+1)%n], p) == CNEITHER) return BOUNDARY;

    for (i = 0, j = n-1; i < n; j = i++)
        if (((poly[i].y <= p.y && p.y < poly[j].y) ||
             (poly[j].y <= p.y && p.y < poly[i].y)) &&
            (p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y) /
             (poly[j].y - poly[i].y) + poly[i].x))
            c = !c;
    return c;
}


Point inf(Point r) {
    return 2*1e6 / len(r) * r;
}

Point R(Point r, double theta) {
    return Point(cos(theta) * r.x - sin(theta) * r.y,
                 sin(theta) * r.x + cos(theta) * r.y);
}

const Point O(0, 0);

struct Shape {
    vector<Point> corner;
    void scale(double s) {
        // double s = isect_ratio(r);
        for (auto &c: corner) c = s * c;
    }
    double area() { return abs(area_polygon(corner.data(), corner.size())); }

    Shape(int n, double s) {
        corner = vector<Point>(n);
        Point x(s, 0);
        for (int i = 0; i < n; i++) {
            corner[i] = R(x, i * 2 * M_PI / (double)n);
        }
    }
};

vector<Point> P;

bool check_in(int n, double s) {
    Shape S(n, s);
    for (auto &pt: P) {
        if (!point_in_poly(S.corner.data(), n, pt))
            return false;
    }
    return true;
}

bool check_out(int n, double s) {
    Shape S(n, s);
    for (auto pt: P) {
        if (point_in_poly(S.corner.data(), n, pt))
            return false;
    }
    return true;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

    int n;
    cin >> n;
    P.resize(n);
    for (auto &p: P) cin >> p.x >> p.y;

    double s_max = -1;
    int k = -1;
    for (int i = 8; i >= 3; i--) {
        double lo = EPS;
        double hi = 1.0;
        while (!check_in(i, hi)) hi *= 2;
        while (abs(hi - lo) > EPS) {
            double mid = hi - ((hi - lo) / 2);
            (check_in(i, mid) ? hi : lo) = mid;
        }

        Shape outer(i, lo);

        lo = EPS;
        hi = 0.9;
        while (check_out(i, hi)) hi *= 2;
        while (abs(hi - lo) > EPS) {
            double mid = hi - ((hi - lo) / 2);
            (check_out(i, mid) ? lo : hi) = mid;
        }

        Shape inner(i, lo);
        double t = inner.area() / outer.area();
        if (t > s_max) {
            k = i;
            s_max = t;
        }
    }
    cout << k << ' ' << fixed << setprecision(10) << s_max << endl;
}

