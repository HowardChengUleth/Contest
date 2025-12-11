#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

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

int64_t count_path(int start, int goal)
{
  if (start == goal) {
    return 1;
  }

  int64_t &ans = memo[start];
  if (ans >= 0) {
    return ans;
  }

  ans = 0;
  for (auto v : G[start]) {
    ans += count_path(v, goal);
  }

  return ans;
}

int64_t count_path(string from, string to)
{
  memo.resize(G.size());
  fill(begin(memo), end(memo), -1);
  return count_path(dev2index(from), dev2index(to));
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

  if (G.size() < dev2index("out")+1) {
    G.resize(dev2index("out")+1);
  }

  
  auto a1 = count_path("svr", "fft");
  auto a2 = count_path("fft", "dac");
  auto a3 = count_path("dac", "out");

  auto b1 = count_path("svr", "dac");
  auto b2 = count_path("dac", "fft");
  auto b3 = count_path("fft", "out");

  auto a = a1 * a2 * a3;
  auto b = b1 * b2 * b3;

  cout << "a + b = " << a+b << endl;
  
  return 0;
}
