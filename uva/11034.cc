#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> sides[2];   // 0 = left, 1 = right
int l, m;

void read_case(void)
{
  sides[0].clear();
  sides[1].clear();
  cin >> l >> m;
  l *= 100;
  for (int i = 0; i < m; i++) {
    int len;
    string side;
    cin >> len >> side;
    sides[side == "right"].push_back(len);
  }
}

void solve_case(void)
{
  int trips = 0;
  int side = 0;
  unsigned int index[2] = {0,0};

  while (index[0] < sides[0].size() || index[1] < sides[1].size()) {
    // pick up cars from current side
    int sum = 0;
    while (index[side] < sides[side].size() && 
	   sum + sides[side][index[side]] <= l) {
      sum += sides[side][index[side]++];
    }

    // now cross
    side = 1 - side;
    trips++;
  }

  cout << trips << endl;
}

int main(void)
{
  int c;

  cin >> c;

  while (c-- > 0) {
    read_case();
    solve_case();
  }
  return 0;
}
