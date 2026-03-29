// use Green's theorem: look at all intersection of circles and for
// each circle, those points divide the circle into arcs.  For each
// arc decide if it is "inside" or "outside".  Take all the "outside"
// curves and add up the line integrals

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1);

struct Circle {
    double x, y, r;
};

double sq(double x) { return x * x; }

double dist(double x1, double y1, double x2, double y2) {
    return sqrt(sq(x1 - x2) + sq(y1 - y2));
}

bool inside(const Circle &c, double x, double y) {
    return dist(c.x, c.y, x, y) < c.r - EPS;
}

double norm(double a) {
    while (a < 0) a += 2 * PI;
    while (a >= 2 * PI) a -= 2 * PI;
    return a;
}

// Safe acos to avoid NaN due to precision
double safe_acos(double x) {
    if (x < -1) x = -1;
    if (x > 1) x = 1;
    return acos(x);
}

double union_area(vector<Circle> &circles) {
    int n = circles.size();
    double total_area = 0.0;

    for (int i = 0; i < n; i++) {
        vector<double> angles;
        angles.push_back(0);
        angles.push_back(2 * PI);

        bool covered = false;

        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            double d = dist(circles[i].x, circles[i].y,
                            circles[j].x, circles[j].y);

            // Same center case
            if (d < EPS) {
                if (circles[i].r <= circles[j].r + EPS) {
                    covered = true;
                    break;
                }
                continue;
            }

            // Fully inside
            if (d + circles[i].r <= circles[j].r + EPS) {
                covered = true;
                break;
            }

            // No meaningful intersection (including tangency)
            if (d >= circles[i].r + circles[j].r - EPS ||
                d <= fabs(circles[i].r - circles[j].r) + EPS) {
                continue;
            }

            // Compute intersection angles
            double base = atan2(circles[j].y - circles[i].y,
                                circles[j].x - circles[i].x);

            double val = (sq(circles[i].r) + sq(d) - sq(circles[j].r)) /
                         (2 * circles[i].r * d);

            double angle = safe_acos(val);

            double a1 = norm(base - angle);
            double a2 = norm(base + angle);

            angles.push_back(a1);
            angles.push_back(a2);
        }

        if (covered) continue;

        // Sort and deduplicate angles
        sort(angles.begin(), angles.end());
        vector<double> unique_angles;
        for (double a : angles) {
            if (unique_angles.empty() ||
                fabs(a - unique_angles.back()) > EPS) {
                unique_angles.push_back(a);
            }
        }

        // Ensure wrap-around continuity
        if (unique_angles.size() == 1) {
            unique_angles.push_back(unique_angles[0] + 2 * PI);
        }

        int m = unique_angles.size();

        for (int k = 0; k < m; k++) {
            double a1 = unique_angles[k];
            double a2 = (k + 1 < m) ? unique_angles[k + 1]
                                   : unique_angles[0] + 2 * PI;

            if (a2 - a1 < EPS) continue;

            double mid = (a1 + a2) / 2;

            double x = circles[i].x + circles[i].r * cos(mid);
            double y = circles[i].y + circles[i].r * sin(mid);

            bool inside_other = false;
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (inside(circles[j], x, y)) {
                    inside_other = true;
                    break;
                }
            }
            if (inside_other) continue;

            double theta = a2 - a1;

            double area = 0.5 * circles[i].r * circles[i].r * theta
                + 0.5 * (
                    circles[i].x * circles[i].r * (sin(a2) - sin(a1))
                  - circles[i].y * circles[i].r * (cos(a2) - cos(a1))
                );

            total_area += area;
        }
    }

    return total_area;
}

int main() {
    int n;
    cin >> n;

    vector<Circle> circles;

    for (int i = 0; i < n; i++) {
        Circle c;
        cin >> c.r >> c.x >> c.y;

        bool duplicate = false;
        for (auto &d : circles) {
            if (fabs(c.x - d.x) < EPS &&
                fabs(c.y - d.y) < EPS &&
                fabs(c.r - d.r) < EPS) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) circles.push_back(c);
    }

    cout << fixed << setprecision(10)
         << union_area(circles) << endl;

    return 0;
}
