#include <bits/stdc++.h>

using namespace std;

int dist2(int x, int y)
{
  int dx = x - 144;
  int dy = y - 84;

  return dx*dx + dy*dy;
}

void add_score(vector<int> x[], vector<int> y[], int score[])
{
  int total[2];
  int closest[2] = { INT_MAX, INT_MAX };
  
  for (int i = 0; i < 2; i++) {
    total[i] = x[i].size();
    for (int k = 0; k < total[i]; k++) {
      int d = dist2(x[i][k], y[i][k]);
      closest[i] = min(closest[i], d);
    }
  }

  int winner = min_element(closest, closest+2) - closest;
  int loser = 1 - winner;
  for (int k = 0; k < total[winner]; k++) {
    if (dist2(x[winner][k], y[winner][k]) < closest[loser]) {
      score[winner]++;
    }
  }


}

int main()
{
  int score[2] = {0};

  for (int i = 0; i < 10; i++) {
    vector<int> x[2], y[2];
    for (int j = 0; j < 2; j++) {
      int n;
      cin >> n;
      while (n--) {
	int xx, yy;
	cin >> xx >> yy;
	x[j].push_back(xx);
	y[j].push_back(yy);
      }
    }


    add_score(x, y, score);

  }

  for (int i = 0; i < 2; i++) {
    cout << score[i] << ' ';
  }
  cout << endl;


  return 0;
}
