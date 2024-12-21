#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef long long ll;

vector<string> numpad{ "789", "456", "123", " 0A" };
vector<string> dirpad{ " ^A", "<v>" };

const string dirchar = "^v<>";
const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

bool inside_npad(int r, int c)
{
  if (r == 3) {
    return 1 <= c && c <= 2;
  }
  return (0 <= r && r < 3 && 0 <= c && c < 3);
}

bool inside_dpad(int r, int c)
{
  if (r == 0) {
    return 1 <= c && c <= 2;
  }
  return r == 1 && (0 <= c && c <= 2);
}



struct State
{
  string code;
  int code_pos;

  int dir1_r, dir1_c;
  int dir2_r, dir2_c;
  int num_r, num_c;
  
  State(string C)
    : code(C), code_pos(0),
      dir1_r(0), dir1_c(2),
      dir2_r(0), dir2_c(2),
      num_r(3), num_c(2)
  {
  }

  bool goal() const
  {
    return code_pos == (int)code.length();
  }

  ll hash() const
  {
    ll val = code_pos;
    val = val * 4 + dir1_r;
    val = val * 4 + dir1_c;
    val = val * 4 + dir2_r;
    val = val * 4 + dir2_c;
    val = val * 4 + num_r;
    val = val * 4 + num_c;
    return val;
  }

  bool operator<(const State &s) const
  {
    return hash() < s.hash();
  }
  
  bool move(int dir, int level = 0)
  {
    assert(level <= 2);
    
    if (level == 0) {
      int r2 = dir1_r + dr[dir];
      int c2 = dir1_c + dc[dir];
      if (!inside_dpad(r2, c2))
	return false;
      dir1_r = r2;
      dir1_c = c2;
      return true;
    } else if (level == 1) {
      int r2 = dir2_r + dr[dir];
      int c2 = dir2_c + dc[dir];
      if (!inside_dpad(r2, c2))
	return false;
      dir2_r = r2;
      dir2_c = c2;
      return true;
    } else if (level == 2) {
      int r2 = num_r + dr[dir];
      int c2 = num_c + dc[dir];
      if (!inside_npad(r2, c2))
	return false;
      num_r = r2;
      num_c = c2;
      return true;
    }
    return false;
  }

  bool accept(int level = 0)
  {
    if (level == 0) {
      char d = dirpad[dir1_r][dir1_c];
      if (d == 'A') {
	return accept(1);
      } else {
	int dir = dirchar.find(d);
	return move(dir, 1);
      }
    } else if (level == 1) {
      char d = dirpad[dir2_r][dir2_c];
      if (d == 'A') {
	return accept(2);
      } else {
	int dir = dirchar.find(d);
	return move(dir, 2);
      }
    } else if (level == 2) {
      char d = numpad[num_r][num_c];
      if (code_pos < (int)code.length() && d == code[code_pos]) {
	code_pos++;
	return true;
      } else {
	return false;
      }
    }
    assert(false);
    return false;
  }
};

ostream &operator<<(ostream &os, const State &s)
{
  os << "pos = " << s.code_pos << endl;
  os << "  dir1 = " << s.dir1_r << ", " << s.dir1_c << endl;
  os << "  dir2 = " << s.dir2_r << ", " << s.dir2_c << endl;
  os << "  num  = " << s.num_r << ", " << s.num_c << endl;
  return os;
}

ll complexity(string code)
{
  State start(code);

  queue<State> Q;
  map<State, int> dist;

  dist[start] = 0;
  Q.push(start);

  while (!Q.empty()) {
    auto curr = Q.front();
    Q.pop();

    if (curr.goal()) {
      return dist[curr] * (ll)stoi(code.substr(0,3));
    }
      
    State next = curr;
    if (next.accept()) {
      if (dist.find(next) == dist.end()) {
	Q.push(next);
	dist[next] = dist[curr] + 1;
      }
    }

    for (int dir = 0; dir < 4; dir++) {
      next = curr;
      if (!next.move(dir)) continue;
      if (dist.find(next) != dist.end()) continue;
      Q.push(next);
      dist[next] = dist[curr] + 1;
    }
  }
  

  return 0;
}

int main()
{
  ll ans = 0;
  string code;
  while (cin >> code) {
    ans += complexity(code);
  }
  cout << ans << endl;
  return 0;
}
