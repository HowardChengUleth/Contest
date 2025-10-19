// Not much to say...just do it.
//
// Normally we do not want to compare <= with doubles, but because we are
// only comparing the input without doing any calculations, it is good
// enough.
//
// To be really proper, note that they say there are 4 decimal digits.
// So read the number as two integers (skipping over the . in between)
// and convert a.b to a * 10000 + b.  Then you will not have to worry
// about any rounding errors.
#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  while (n--) {
    double lon, lat;
    cin >> lon >> lat;

    if (-180 <= lon && lon <= 180 && -90 <= lat && lat <= 90) {
      cout << "VALID" << endl;
    } else {
      cout << "INVALID" << endl;
    }
  }

  return 0;
}
