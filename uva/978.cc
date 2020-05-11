#include <iostream>
#include <queue>

using namespace std;

void solve()
{
  int B, SG, SB;
  cin >> B >> SG >> SB;
  
  priority_queue<int> green, blue;
  for (int i = 0; i < SG; i++) {
    int s;
    cin >> s;
    green.push(s);
  }
  for (int i = 0; i < SB; i++) {
    int s;
    cin >> s;
    blue.push(s);
  }

  while (!green.empty() && !blue.empty()) {
    int green_surv[100000], blue_surv[100000];
    int n_g = 0, n_b = 0;

    for (int i = 0; i < B && !green.empty() && !blue.empty(); i++) {
      int g = green.top(); green.pop();
      int b = blue.top(); blue.pop();
      if (g > b) {
	green_surv[n_g++] = g-b;
      } else if (g < b) {
	blue_surv[n_b++] = b-g;
      }
    }

    for (int i = 0; i < n_g; i++) {
      green.push(green_surv[i]);
    }
    for (int i = 0; i < n_b; i++) {
      blue.push(blue_surv[i]);
    }
  }

  if (green.empty() && blue.empty()) {
    cout << "green and blue died" << endl;
  } else if (blue.empty()) {
    cout << "green wins" << endl;
    while (!green.empty()) {
      cout << green.top() << endl;
      green.pop();
    }
  } else {
    cout << "blue wins" << endl;
    while (!blue.empty()) {
      cout << blue.top() << endl;
      blue.pop();
    }
  }
}

int main(void)
{
  int N;
  cin >> N;
  while (N--) {
    solve();
    if (N) cout << endl;
  }
  return 0;
}
