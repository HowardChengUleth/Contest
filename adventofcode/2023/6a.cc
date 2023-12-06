#include <bits/stdc++.h>

using namespace std;

void read_vec(vector<int> &v)
{
  string dummy, line;
  cin >> dummy;
  getline(cin, line);
  istringstream iss(line);
  int x;
  while (iss >> x) {
    v.push_back(x);
  }
}

int find_ways(int t, int d)
{
  int count = 0;
  for (int hold = 0; hold <= t; hold++) {
    int speed = hold;
    int dist = (t - hold) * speed;
    if (dist > d) {
      count++;
    }
  }
  return count;
}

int main()
{
  string dummy, line;

  vector<int> time, dist;
  read_vec(time);
  read_vec(dist);

  int n = time.size();
  long long ans = 1;
  for (int i = 0; i < n; i++) {
    ans *= find_ways(time[i], dist[i]);
  }
  cout << ans << endl;

  return 0;
}
