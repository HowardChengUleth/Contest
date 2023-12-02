#include <bits/stdc++.h>

using namespace std;

bool possible(const string &line, int &id)
{
  istringstream iss(line);

  string dummy;
  iss >> dummy >> id >> dummy;
  assert(dummy == ":");

  const string color_name[] = {"red", "green", "blue"};
  const int start[] = {12, 13, 14};
  
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
	if (curr[i] > start[i]) return false;
	curr[i] = 0;
      }
    }
  }
  return true;
}

int main()
{
  string line;
  int ans = 0;
  
  while (getline(cin, line)) {
    int id;
    if (possible(line, id)) {
      ans += id;
    }
  }

  cout << ans << endl;
  return 0;
}
