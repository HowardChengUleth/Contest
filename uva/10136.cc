#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

const double EPS = 1e-8;

int count_pts(double cx, double cy, double x[], double y[], int n)
{
  int count = 0;
  for (int i = 0; i < n; i++) {
    double dx = cx - x[i], dy = cy - y[i];
    if (dx*dx + dy*dy <= 6.25+EPS) {
      //      cout << "            (" << cx << ", " << cy << "): ";
      //     cout << "  (" << x[i] << ", " << y[i] << "): " << count << endl; 
      count++;
    }
  }
  return count;
}

int count(double x[], double y[], int n, int i, int j)
{
  double dx = x[i] - x[j], dy = y[i] - y[j];
  double dist_sq = dx * dx + dy * dy;
  double mx = (x[i] + x[j])/2, my = (y[i] + y[j])/2;

  double temp = 6.25 - dist_sq/4;
  if (temp < 0) {
    return 0;
  }

  dx /= sqrt(dist_sq);
  dy /= sqrt(dist_sq);
  dx *= sqrt(temp);
  dy *= sqrt(temp);

  //  cout << "    (" << x[i] << ", " << y[i] << ")" << endl;
  //  cout << "    (" << x[j] << ", " << y[j] << ")" << endl;

  return max(count_pts(mx - dy, my + dx, x, y, n),
	     count_pts(mx + dy, my - dx, x, y, n));
}

int main(void)
{
  int T;
  cin >> T;
  cin.ignore(1);
  cin.ignore(1);

  while (T-- > 0) {
    double x[200], y[200];
    int n = 0;
    
    string line;
    while (getline(cin, line) && line != "") {
      istringstream iss(line);
      iss >> x[n] >> y[n];
      n++;
    }

    int best = 1;
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) {
	if (fabs(x[i] - x[j]) < EPS && fabs(y[i] - y[j]) < EPS) continue;
	int temp = count(x, y, n, i, j);
	if (temp > best) {
	  best = temp;
	  //	  cout << "best = " << best << endl;
	  //	  cout << " (" << x[i] << ", " << y[i] << ")" << endl;
	  //	  cout << " (" << x[j] << ", " << y[j] << ")" << endl;
	}
      }
    }

    cout << best << endl;
    if (T) {
      cout << endl;
    }
  }
  
}
