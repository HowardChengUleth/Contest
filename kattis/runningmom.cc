#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<int>> G;
map<string,int> ID;

int getID(const string &city)
{
  if (ID.find(city) == ID.end()) {
    int s = ID.size();
    ID[city] = s;
  }
  return ID[city];
}

bool cycle(int v, vector<bool> &visited)
{
  visited[v] = true;
  for (auto w : G[v]) {
    if (visited[w] || cycle(w, visited)) {
      return true;
    }
  }
  visited[v] = false;
  return false;
}

bool cycle(int v)
{
  vector<bool> visited(2*n, false);
  return cycle(v, visited);
}

int main()
{
  cin >> n;
  G.resize(2*n);    // at most 2*n cities

  for (int i = 0; i < n; i++) {
    string city1, city2;
    cin >> city1 >> city2;
    int id1 = getID(city1), id2 = getID(city2);
    G[id1].push_back(id2);
  }

  string city;
  while  (cin >> city) {
    cout << city << ' ';
    if (cycle(getID(city))) {
      cout << "safe";
    } else {
      cout << "trapped";
    }
    cout << endl;
  }

  return 0;
}
