#include <bits/stdc++.h>

using namespace std;

typedef vector<pair<int,string>> vpis;
typedef vector<string> vs;

map<string, vpis> G;
map<string, vs> parent;

void wipe(string &line, string kw)
{
  string::size_type it;
  while ((it = line.find(kw)) != string::npos) {
    line.replace(it, kw.length(), " ");
  }
}

void parse(string line)
{
  const string kw[] = { ",", ".", "contain", "bags", "bag" };
  for (int i = 0; i < 5; i++) {
    wipe(line, kw[i]);
  }

  istringstream iss(line);
  string s;
  string color;
  iss >> s;
  color += s + ' ';
  iss >> s;
  color += s;

  if (line.find("no other") != string::npos) {
    G[color].clear();
    return;
  }

  int n;
  while (iss >> n) {
    string child;
    iss >> s;
    child += s + ' ';
    iss >> s;
    child += s;
    parent[child].push_back(color);
    G[color].emplace_back(n, child);
  }
}

int solveA()
{
  set<string> visited;
  queue<string> q;

  q.push("shiny gold");
  visited.insert("shiny gold");

  while (!q.empty()) {
    string curr = q.front();
    q.pop();
    for (auto s : parent[curr]) {
      if (visited.count(s)) continue;
      q.push(s);
      visited.insert(s);
    }
  }
  
  return visited.size()-1;
}

map<string,int> bags;

long long solveB(string s)
{
  if (bags.find(s) != bags.end())
    return bags[s];

  if (G.find(s) == G.end()) {
    return bags[s] = 1;
  }

  long long ans = 1;
  for (auto p : G[s]) {
    int num = p.first;
    string c = p.second;
    ans += num * solveB(c);
  }

  return bags[s] = ans;
}

int solveB()
{
  return solveB("shiny gold") - 1;
}

int main()
{
  string line;
  while (getline(cin, line)) {
    parse(line);
  }

  cout << "A = " << solveA() << endl;
  cout << "B = " << solveB() << endl;
  
  return 0;
}
