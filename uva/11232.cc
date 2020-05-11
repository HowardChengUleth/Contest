#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

int main(void)
{
  double w, h;
  double pi = acos(-1.0);
  while (cin >> w >> h && (w > 0.5 && h > 0.5)) {
    if (w > h) {
      swap(w, h);
    }

    double vol;

    // horizontal roll up
    vol = w * pi * pow((min(w, h/(pi+1)))/2, 2.0);
    
    // vertical roll up
    vol = max(vol, (h - w/pi) * (pi * pow(w/pi/2, 2.0)));
    if (w/pi >= 2*h/3) {
      vol = max(vol, (h/3) * (pi * h*h/9));
    }
    cout << fixed << setprecision(3) << vol << endl;
  }
  return 0;
}
