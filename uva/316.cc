#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>

using namespace std;

typedef pair<int,int> pii;
typedef map<pii, int> Map;

const double EPS = 1e-4;

bool match(pii c1, pii c2, const Map &cons,
	   pii s1, pii s2, const Map &stars,
	   int &brightness, Map &matched)
{
  int dx1 = c2.first - c1.first, dy1 = c2.second - c1.second;
  int dx2 = s2.first - s1.first, dy2 = s2.second - s1.second;

  double len1 = sqrt(dx1*dx1 + dy1*dy1),
    len2 = sqrt(dx2*dx2 + dy2*dy2);

  double angle = atan2(dy2, dx2) - atan2(dy1, dx1);

  brightness = 0;
  matched.clear();

  for (auto c : cons) {

    
    double x = c.first.first, y = c.first.second;
    x -= c1.first;  y -= c1.second;

    // scale and rotate
    x *= len2/len1;  y *= len2/len1;

    double xx = x*cos(angle) - y*sin(angle);
    double yy = x*sin(angle) + y*cos(angle);

    xx += s1.first;  yy += s1.second;

    int rx = floor(xx+0.5), ry = floor(yy+0.5);
    if (fabs(xx-rx) > EPS || fabs(yy-ry) > EPS)
      return false;

    auto it = stars.find(pii(rx,ry));
    if (it == stars.end())
      return false;

    brightness += it->second;
    matched[pii(rx,ry)] = 1;
  }
  
  return true;
}
	   
int match(const Map &cons, const Map &stars, int &brightness, Map &matched)
{
  // special case: only one star in constellation
  brightness = 0;
  matched.clear();
  
  if (cons.size() == 1) {
    brightness = stars.begin()->second;
    matched[stars.begin()->first] = 1;
    return stars.size();
  }

  // p1, p2 are the first two stars in constellation
  auto it_cons = cons.begin();
  pii p1 = it_cons->first;
  ++it_cons;
  pii p2 = it_cons->first;

  // go through all pairs of stars
  int ans = 0;
  for (auto s1 : stars) {
    for (auto s2 : stars) {
      if (s1 == s2) continue;

      int btemp;
      Map matched_temp;
      if (match(p1, p2, cons, s1.first, s2.first, stars, btemp, matched_temp)) {
	ans++;
	if (btemp > brightness) {
	  brightness = btemp;
	  matched.swap(matched_temp);
	}
      }
    }
  }

  return ans;
}

bool solve(int id)
{
  int n;
  cin >> n;
  if (!n) return false;

  Map stars;
  for (int i = 0; i < n; i++) {
    int x, y, b;
    cin >> x >> y >> b;
    stars[pii(x,y)] = b;
  }

  int brightness;
  Map matched;

  int m;
  cin >> m;
  Map cons[50];
  string name[50];
  int aut[50];
  for (int i = 0; i < m; i++) {
    int s;
    cin >> s >> name[i];
    for (int j = 0; j < s; j++) {
      int x, y;
      cin >> x >> y;
      cons[i][pii(x,y)] = 1;
    }
    aut[i] = match(cons[i], cons[i], brightness, matched);
  }

  cout << "Map #" << id << endl;

  for (int i = 0; i < m; i++) {
    int times = match(cons[i], stars, brightness, matched) / aut[i];
    cout << endl
	 << name[i] << " occurs " << times << " time(s) in the map." << endl;
    cout << "Brightest occurrence:";
    for (auto p : matched) {
      cout << " (" << p.first.first << "," << p.first.second << ")";
    }
    cout << endl;
  }
  
  cout << "-----" << endl;

  
  

  return true;
}

int main()
{
  int id = 1;
  while (solve(id++))
    ;
  
  return 0;
}
