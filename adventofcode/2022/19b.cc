#include <bits/stdc++.h>

using namespace std;

enum Resource {
  ORE, CLAY, OBS, GEODE
};

const int MAX_TIME = 32;

struct State
{
  int t;
  int robot[4];
  int resource[4];

  State()
  {
    t = 0;
    fill(robot, robot+4, 0);
    fill(resource, resource+4, 0);
  }
  
  bool operator<(const State &s) const
  {
    if (t != s.t) return t < s.t;
    if (!equal(robot, robot+4, s.robot)) {
      return lexicographical_compare(robot, robot+4, s.robot, s.robot+4);
    }

    // don't look at geode resources
    return lexicographical_compare(resource, resource+3,
				   s.resource, s.resource+3);
  }
};

ostream &operator<<(ostream &os, const State &s)
{
  os << "(" << s.t;
  for (int i = 0; i < 4; i++) {
    os << ", " << s.robot[i];
  }
  os << "| ";
  for (int i = 0; i < 4; i++) {
    os << ", " << s.resource[i];
  }
  return os << ")";
}

bool can_build(const State &curr, int cost[4][4], int type)
{
  for (int i = 0; i < 4; i++) {
    if (curr.resource[i] < cost[type][i]) return false;
  }

  return true;
}

State build(const State &curr, int cost[4][4], int type)
{
  State next = curr;
  for (int i = 0; i < 4; i++) {
    next.resource[i] -= cost[type][i];
  }
  next.robot[type]++;
  return next;
}

State collect(const State &curr)
{
  State next = curr;
  for (int type = 0; type < 4; type++) {
    next.resource[type] += next.robot[type];
  }
  next.t++;
  return next;
}

void push(stack<State> &q, map<State, int> &best, const State &s)
{
  int val = s.resource[GEODE];
  if (best.find(s) == best.end() || val > best[s]) {
    best[s] = val;
    q.push(s);
  }
}

bool dont_build(const State &curr, int cost[4][4], int type)
{
  int rem = MAX_TIME - curr.t;

  int need = 0;
  for (int i = 0; i < 4; i++) {
    need = max(need, cost[i][type]);
  }
  return (curr.robot[type] >= need);
}

int max_geode(const State &s)
{
  int rem = MAX_TIME - s.t;
  int curr_num = s.robot[GEODE];

  int ans = s.resource[GEODE];

  // assume you get one geode robot each step
  for (int i = 0; i < rem; i++) {
    ans += curr_num;
    curr_num++;
  }
  
  return ans;
}

int solve(string line)
{
  int dummy, a, b, c, d, e, f;
  sscanf(line.c_str(), "Blueprint %d: "
	 "Each ore robot costs %d ore. "
	 "Each clay robot costs %d ore. "
	 "Each obsidian robot costs %d ore and %d clay. "
	 "Each geode robot costs %d ore and %d obsidian.",
	 &dummy, &a, &b, &c, &d, &e, &f);

  int robot_cost[4][4] = { { a, 0, 0, 0 },
                           { b, 0, 0, 0 },
			   { c, d, 0, 0 },
			   { e, 0, f, 0 } };

  stack<State> q;
  map<State, int> best;
  State init;
  init.robot[ORE] = 1;
  q.push(init);
  best[init] = 0;

  int ans = 0;
  while (!q.empty()) {
    State curr = q.top();
    q.pop();

    // time's up
    if (curr.t == MAX_TIME) {
      ans = max(ans, best[curr]);
      continue;
    }

    // prune if we cannot get more than what we have now
    if (max_geode(curr) <= ans) {
      continue;
    }

    // if you can build geode robot, always build one
    if (can_build(curr, robot_cost, GEODE)) {
      State next = collect(curr);
      next = build(next, robot_cost, GEODE);
      push(q, best, next);
      continue;
    }
    
    // try building each of the other type of robots
    int can_build_count = 0;
    int build_count = 0;
    for (int t = ORE; t <= OBS; t++) {
      if (can_build(curr, robot_cost, t)) {
	can_build_count++;

	// don't build a robot if we already have too much resources
	if (!dont_build(curr, robot_cost, t)) {
	  State next = collect(curr);
	  next = build(next, robot_cost, t);
	  push(q, best, next);
	  build_count++;
	}
      }
    }

    // don't build anything, but only if it is not possible to build everything
    if (can_build_count < 3 || build_count == 0) {
      State next = collect(curr);
      push(q, best, next);
    }
  }

  return ans;
}

int main()
{
  string line;
  int id = 1;
  int ans = 1;
  while (getline(cin, line) && id <= 3) {
    int geode = solve(line);
    cout << "ID = " << id << ": " << geode << endl;
    id++;
    ans *= geode;
  }

  cout << ans << endl;
  return 0;
}
