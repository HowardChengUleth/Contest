#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

// Great Circle distance between two points using Heaverside formula
//
// Author: Howard Cheng
// Reference: http://mathforum.org/library/drmath/view/51879.html
//
// Given two points specified by their latitudes and longitudes, as well
// as the radius of the sphere, return the shortest distance between the
// two points along the surface of the sphere.
//
// latitude should be between -90 to 90 degrees (inclusive), and
// longitude should be between -180 to 180 degrees (inclusive)

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double greatcircle(double lat1, double long1, double lat2, double long2,
		   double radius)
{
  const double PI = acos(-1.0);

  lat1 *= PI/180.0;
  lat2 *= PI/180.0;
  long1 *= PI/180.0;
  long2 *= PI/180.0;
  
  double dlong = long2 - long1;
  double dlat = lat2 - lat1;
  double a = sin(dlat/2)*sin(dlat/2) +
    cos(lat1)*cos(lat2)*sin(dlong/2)*sin(dlong/2);
  return radius * 2 * atan2(sqrt(a), sqrt(1-a));
}

int main(void)
{
  int N, M, Q;
  int case_num = 1;
  while (cin >> N >> M >> Q && (N || M || Q)) {
    if (case_num > 1) {
      cout << endl;
    }
    cout << "Case #" << case_num++ << endl;
    string city[100];
    double lat[100], lon[100];

    for (int i = 0; i < N; i++) {
      cin >> city[i] >> lat[i] >> lon[i];
    }

    double D[100][100];
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
	D[i][j] = -1;
      }
      D[i][i] = 0;
    }

    for (int i = 0; i < M; i++) {
      string city1, city2;
      cin >> city1 >> city2;
      int index1 = find(city, city+N, city1) - city;
      int index2 = find(city, city+N, city2) - city;
      D[index1][index2] = 
	floor(greatcircle(lat[index1], lon[index1], lat[index2], lon[index2],
			  6378)+0.5);
    }

    for (int k = 0; k < N; k++) {
      for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	  if (D[i][k] < 0 || D[k][j] < 0) continue;
	  double t = D[i][k] + D[k][j];
	  if (D[i][j] < 0 || t < D[i][j]) {
	    D[i][j] = floor(t + 0.5);
	  }
	}
      }
    }

    for (int i = 0; i < Q; i++) {
      string city1, city2;
      cin >> city1 >> city2;
      int index1 = find(city, city+N, city1) - city;
      int index2 = find(city, city+N, city2) - city;
      if (D[index1][index2] < 0) {
	cout << "no route exists" << endl;
      } else {
	cout << fixed << setprecision(0) << D[index1][index2]
	     << " km" << endl;
      }
    }      
  }
  return 0;
}

