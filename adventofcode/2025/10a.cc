#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int M, N;

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

int num_lights;

int search(vector<bool> &state, const vector<bool> &goal,
	   const vector<vector<bool>> &buttons, int index)
{
  if (index >= (int)buttons.size()) {
    if (state == goal)
      return 0;
    else
      return 1000000;
  }

  int ans1 = search(state, goal, buttons, index+1);

  for (int i = 0; i < num_lights; i++) {
    if (buttons[index][i]) {
      state[i] = !state[i];
    }
  }

  int ans2 = search(state, goal, buttons, index+1) + 1;
  
  for (int i = 0; i < num_lights; i++) {
    if (buttons[index][i]) {
      state[i] = !state[i];
    }
  }

  return min(ans1, ans2);
}

int process(string line)
{
  num_lights = line.find(']') - (line.find('[') + 1);
  vector<bool> goal(num_lights);
  for (int i = 0; i < num_lights; i++) {
    goal[i] = line[i+1] == '#';
  }

  vector<vector<bool>> buttons;
  line.erase(0, num_lights+2);
  replace(begin(line), end(line), ',', ' ');
  replace(begin(line), end(line), ')', '\n');
  istringstream iss(line);
  char ch;
  while (iss >> ch && ch == '(') {
    string str;
    getline(iss, str);
    istringstream iss2(str);

    vector<bool> v(num_lights, false);
    int pos;
    while (iss2 >> pos) {
      v[pos] = true;
    }
    buttons.push_back(v);
  }

  vector<bool> init(num_lights, false);
  return search(init, goal, buttons, 0);
}

int main()
{
  string line;

  int64_t ans = 0;
  while (getline(cin, line)) {
    ans += process(line);
  }

  cout << ans << endl;
  return 0;
}
