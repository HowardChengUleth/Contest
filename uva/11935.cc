// just do it, carefully
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

bool do_case()
{
  string event;
  int curr_d, prev_d;
  double cons = 0;
  int leak = 0;
  double tank = 0.0;
  double used = 0.0;
  
  cin >> prev_d;
  cin >> event;
  cin >> event;
  cin >> cons;
  if (cons == 0) return false;

  while (true) {
    cin >> curr_d >> event;
    used += (curr_d - prev_d) * (cons / 100.0 + leak);
    tank = max(tank, used);
    if (event == "Fuel") {
      cin >> event >> cons;
    } else if (event == "Leak") {
      leak++;
    } else if (event == "Goal") {
      break;
    } else if (event == "Mechanic") {
      leak = 0;
    } else if (event == "Gas") {
      cin >> event;
      used = 0.0;
    }

    prev_d = curr_d;
  }
  
  cout << fixed << setprecision(3) << tank << endl;
  return true;
}

int main(void)
{
  while (do_case())
    ;
  return 0;
}
