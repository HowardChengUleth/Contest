#include <bits/stdc++.h>

using namespace std;

int main()
{
  const string heading[] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW" };

  string curr, dest;
  cin >> curr >> dest;

  int ci = find(heading, heading+8, curr) - heading;
  int di = find(heading, heading+8, dest) - heading;

  assert(0 <= ci && ci < 8);
  assert(0 <= di && di < 8);

  if (ci == di) {
    cout << "Keep going straight" << endl;
  } else if ((ci + 4 - di) % 8 == 0) {
    cout << "U-turn" << endl;
  } else {
    int deg = (di - ci + 8) % 8 * 45;
    string dir;

    if (deg < 180) {
      dir = "starboard";
    } else {
      dir = "port";
      deg = 360 - deg;
    }

    cout << "Turn " << deg << " degrees " << dir << endl;
  }


  return 0;
}
