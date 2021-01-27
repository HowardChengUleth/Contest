#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int h1, m1, h2, m2, alpha;
  char ch;
  cin >> h1 >> ch >> m1 >> h2 >> ch >> m2 >> alpha;

  // At H:M where M is allowed to be a real number, the angle for the
  // hour hand and min hand would be
  //
  //  m = ((H%12)*60+M
  // hour_hand = m/(12*60) 
  // min_hand = (m%60)/60
  //
  // solving for hour_hand = min_hand
  //
  //  m/12 = m%60
  //
  // write m = k*60+M with integer k and real M < 60, we get:
  //
  // 5*k + M/12 = M
  // 5*k = (11/12)*M
  // M = 60*k/11
  //
  // so we see that the answer has to be in 1/11 of a minute.
  //
  // instead of solving everything in closed form, we just simulate.
  //
  // divide the whole circle into chunks so that each chunk is covered
  // by hour hand every 1/11 minute
  // the minute hand moves 12 ticks each 1/11 minute
  
  int ticks = 12*60*11;

  int start = h1*60 + m1;
  int end = h2*60 + m2;

  int ans = 0;
  int hr = (start*11) % ticks;
  int min = (start*12*11) % ticks;
  for (int t = start; t <= end; t++) {
    int hh = t / 60;
    int mm = t % 60;

    for (int f = 0; f < (t == end ? 1 : 11); f++) {
      if (alpha == 0 && hr == min) {
	ans++;
      } else if (alpha == 90) {
	if ((min + ticks/4 - hr) % ticks == 0 ||
	    (min + 3*ticks/4 - hr) % ticks == 0) {
	  ans++;
	}
      } else if (alpha == 180) {
	if ((min + ticks/2 - hr) % ticks == 0) {
	  ans++;
	}
      }

      hr++;
      min += 12;
      hr %= ticks;
      min %= ticks;
    }
  }
  
  cout << ans << endl;

}

int main()
{
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
