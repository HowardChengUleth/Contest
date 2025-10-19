// basic trigonometry...just be careful with radians and degrees.  Also,
// it is generally not so safe to do double comparisons but in this problem
// the sizes of the input make it "safe"

#include <bits/stdc++.h>

using namespace std;

int main()
{
  double D, H;
  cin >> D >> H;

  const double PI = acos(-1.0);
  double theta = 15.0 * PI / 180.0;
  
  double maxH = tan(theta) * D;
  if (H < maxH) {     // this is potentially unsafe
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }

  return 0;
}
