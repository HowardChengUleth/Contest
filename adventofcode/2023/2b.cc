#include <bits/stdc++.h>

using namespace std;

int power(const string &line, int &id)
{
  istringstream iss(line);

  string dummy;
  iss >> dummy >> id >> dummy;
  assert(dummy == ":");

  const string color_name[] = {"red", "green", "blue"};
  int best[] = { 0, 0, 0 };
  
  int num;
  string color;

  int curr[3] = {0};
  while (iss >> num >> color) {
    bool end = false;
    if (color[color.length()-1] == ',') {
      color.erase(color.length()-1);
    } else {
      end = true;
      if (color[color.length()-1] == ';') {
	color.erase(color.length()-1);
      }
    }
    curr[find(color_name, color_name+3, color)-color_name] += num;
    if (end) {
      for (int i = 0; i < 3; i++) {
	best[i] = max(best[i], curr[i]);
	curr[i] = 0;
      }
    }
  }
  return best[0]*best[1]*best[2];
}

int main()
{
  string line;
  int ans = 0;
  
  while (getline(cin, line)) {
    int id;
    ans += power(line, id);
  }

  cout << ans << endl;
  return 0;
}
