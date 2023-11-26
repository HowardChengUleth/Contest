#include <bits/stdc++.h>

using namespace std;

int new_rating = 1500;

int n, m;
long long rating[100001];
long long matches[100001];

void process(int x, int y)
{
  if (!matches[x]) {
    rating[x] = new_rating;
  }
  if (!matches[y]) {
    rating[y] = new_rating;
  }

  long long dx = max(rating[x], (3*rating[y] + rating[x])/2) - rating[x];
  long long dy = rating[y] - min(rating[y], (rating[x] + 3*rating[y])/6);
  //  cout << "dx1, dy1 = " << dx << ' ' << dy << endl;
  
  dx = (matches[y]+1) * dx/(matches[x]+matches[y]+2);
  dy = (matches[x]+1) * dy/(matches[x]+matches[y]+2);
  //  cout << "dx2, dy2 = " << dx << ' ' << dy << endl;
  
  dx = min(1000LL, dx);
  dy = min(1000LL, dy);

  rating[x] += dx;
  rating[y] -= dy;

  matches[x]++;
  matches[y]++;

  cout << rating[x] << ' ' << rating[y] << endl;
  
  if (matches[x] == 1 && matches[y] > 1) {
    new_rating = rating[x];
  } else if (matches[y] == 1 && matches[x] > 1) {
    new_rating = rating[y];
  }
  // cout << "new_rating = " << new_rating << endl;
}


int main()
{
  cin >> n >> m;
  for (int i = 0; i < m ;i++) {
    int x, y;
    cin >> x >> y;

    process(x, y);
  }

  return 0;
}
