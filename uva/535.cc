// Great Circle distance between two points
//
// Author: Howard Cheng
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

#include <utility>
#include <string>
#include <map>

const double radius = 6378;

int main(void)
{
  map< string, pair<double, double> > coord;
  string city;
  while (cin >> city && city != "#") {
    cin >> coord[city].first >> coord[city].second;
  }

  string city1, city2;
  while (cin >> city1 >> city2 && (city1 != "#" || city2 != "#")) {
    cout << city1 << " - " << city2 << endl;
    if (coord.find(city1) == coord.end() ||
	coord.find(city2) == coord.end()) {
      cout << "Unknown" << endl;
    } else {
      cout << fixed << setprecision(0)
	   << greatcircle(coord[city1].first, coord[city1].second,
			  coord[city2].first, coord[city2].second,
			  radius)
	   << " km" << endl;
    }
  }
  
  return 0;
}
