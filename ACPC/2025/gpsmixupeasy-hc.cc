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
