#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

typedef pair<int,int> Node;   // room, state

bool solve(int id)
{
  int r, d, s;
  cin >> r >> d >> s;
  if (r == 0 && d == 0 && s == 0) {
    return false;
  }

  cout << "Villa #" << id << endl;

  vector<int> door[11];
  for (int i = 0; i < d; i++) {
    int u, v;
    cin >> u >> v;
    door[u].push_back(v);
    door[v].push_back(u);
  }

  vector<int> sw[11];
  for (int i = 0; i < s; i++) {
    int k, l;
    cin >> k >> l;
    sw[k].push_back(l);
  }

  map<Node, int> dist;
  map<Node, pair<Node, string> > pred;
  queue<Node> q;

  
  Node start(1, 2);
  Node end(r, (1 << r));
  q.push(start);
  dist[start] = 0;
  pred[start] = make_pair(start, "");
  while (!q.empty()) {
    Node curr = q.front();
    q.pop();
    if (curr == end) goto found;

    int room = curr.first;
    int state = curr.second;

    // try moving to each room
    for (unsigned int i = 0; i < door[room].size(); i++) {
      if ((state & (1 << door[room][i])) == 0) continue;
      Node next(door[room][i], state);
      if (dist.find(next) != dist.end()) continue;
      ostringstream oss;
      oss << "- Move to room " << door[room][i] << ".";
      dist[next] = dist[curr]+1;
      pred[next] = make_pair(curr, oss.str());
      q.push(next);
    }

    // try flipping switches
    for (unsigned int i = 0; i < sw[room].size(); i++) {
      int to = sw[room][i];
      if (to == room) continue;
      Node next(room, (state ^ (1 << to)));
      if (dist.find(next) != dist.end()) continue;
      ostringstream oss;
      oss << "- Switch ";
      if (state & (1 << to)) {
	oss << "off";
      } else {
	oss << "on";
      }
      oss << " light in room " << to << ".";
      dist[next] = dist[curr]+1;
      pred[next] = make_pair(curr, oss.str());
      q.push(next);
    }
  }

  cout << "The problem cannot be solved." << endl;
  return true;
 found:

  cout << "The problem can be solved in " << dist[end] << " steps:" << endl;
  vector<string> path(dist[end]);
  Node curr = end;
  for (int i = dist[end]-1; i >= 0; i--) {
    path[i] = pred[curr].second;
    curr = pred[curr].first;
  }

  for (int i = 0; i < dist[end]; i++) {
    cout << path[i] << endl;
  }
  
  return true;
}

int main(void)
{
  int num = 1;
  while (solve(num++)) {
    cout << endl;
  }
  return 0;
}
