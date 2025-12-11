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

map<string, int> device_map;

int dev2index(const string &dev)
{
  if (device_map.find(dev) != end(device_map)) {
    return device_map[dev];
  }

  int id = device_map.size();
  return device_map[dev] = id;
}

vector<vector<int>> G;
vector<int64_t> memo;

int out_index;

int64_t count_path(int start)
{
  if (start == out_index) {
    return 1;
  }

  int64_t &ans = memo[start];
  if (ans >= 0) {
    return ans;
  }

  ans = 0;
  for (auto v : G[start]) {
    ans += count_path(v);
  }

  return ans;
}

int main()
{
  string line;
  while (getline(cin, line)) {
    replace(begin(line), end(line), ':', ' ');
    istringstream iss(line);
    string from, to;

    iss >> from;

    int from_id = dev2index(from);
    if (G.size() < from_id+1) {
      G.resize(from_id+1);
    }
    while (iss >> to) {
      int to_id = dev2index(to);
      G[from_id].push_back(to_id);
    }
  }

  out_index = dev2index("out");
  memo.resize(G.size(), -1);
  cout << count_path(dev2index("you")) << endl;
  
  return 0;
}
