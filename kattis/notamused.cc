#include <bits/stdc++.h>

using namespace std;

bool process(int day)
{
  string cmd;
  if (!(cin >> cmd))
    return false;
  assert(cmd == "OPEN");

  map<string, int> enter, total;
  while (cin >> cmd && cmd != "CLOSE") {
    string name;
    int time;
    cin >> name >> time;
    if (cmd == "ENTER") {
      enter[name] = time;
    } else {
      total[name] += (time - enter[name]) * 10;
      enter.erase(name);
    }
  }

  if (day > 1) {
    cout << endl;
  }
  cout << "Day " << day << endl;
  for (auto [name, cost] : total) {
    cout << name << " $" << cost/100 << "."
	 << setw(2) << setfill('0') << cost%100 << endl;
  }
  return true;
}

int main()
{
  for (int day = 1; process(day); day++)
    ;

  return 0;
}
