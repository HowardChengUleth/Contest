#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
  int len, light_len, tg, ty, tr, speed, over;
  int case_num = 1;
  while (cin >> len >> light_len >> tg >> ty >> tr >> speed >> over &&
	 (len || light_len || tg || ty || tr || speed || over)) {
    cout << "Case " << case_num++ << ": ";

    int cycle = tg + ty + tr;
    int go = tg + ty;
    double slow_speed = (double)speed / 3600;
    double fast_speed = ((double)speed + over) / 3600;
    double before_light_slow = light_len / slow_speed;
    double before_light_fast = light_len / fast_speed;
    double after_light_slow = (len - light_len) / slow_speed;
    double after_light_fast = (len - light_len) / fast_speed;

    double light_diff = before_light_slow - before_light_fast;
    while (light_diff >= cycle) {
      light_diff -= cycle;
    }

    double wait_diff = 0.0;
    
    // we will just assume that the fast car arrives at time t in the
    // cycle interval.  We will approximate by taking regular intervals
    // since we only need one digit accuracy

    int steps = 100000;
    double size = (double)cycle/steps;

    for (int i = 0; i < steps; i++) {
      double t_fast = i*size;
      double t_slow = t_fast + light_diff;
      while (t_slow >= cycle) {
	t_slow -= cycle;
      }
      double wait_fast = (t_fast <= go) ? 0 : cycle - t_fast;
      double wait_slow = (t_slow <= go) ? 0 : cycle - t_slow;
      wait_diff += wait_slow - wait_fast;
    }

    wait_diff /= steps;

    double ans = before_light_slow + after_light_slow -
      before_light_fast - after_light_fast + wait_diff;
    cout << fixed << setprecision(1) << ans << endl;
  }

  return 0;

}
