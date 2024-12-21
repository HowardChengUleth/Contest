#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef long long ll;

typedef pair<int,int> pii;
typedef vector<string> vs;

const string dirchar = "^v<>";
const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

int finddir(char ch)
{
  return dirchar.find(ch);
}

class KeyPad
{
public:
  vs pad;
  pii pad_pos[256];
  vs memo[256][256];
  
  void init()
  {
    for (int r = 0; r < (int)pad.size(); r++) {
      for (int c = 0; c < (int)pad[0].size(); c++) {
	if (pad[r][c] == ' ') continue;
	pad_pos[(int)pad[r][c]] = pii(r, c);
      }
    }
  }

  bool inside(pii pos) const
  {
    auto [r, c] = pos;
    return (0 <= r && r < (int)pad.size() &&
	    0 <= c && c < (int)pad[0].size() &&
	    pad[r][c] != ' ');
  }

  bool check_cmd(const string &cmd, pii from) const
  {
    pii curr = from;
    for (auto ch : cmd) {
      int dir = finddir(ch);
      curr.first += dr[dir];
      curr.second += dc[dir];
      if (!inside(curr))
	return false;
    }
    return true;
  }
  
  vs find_move(int prev, int next) 
  {
    if (memo[prev][next].size() > 0) {
      return memo[prev][next];
    }
    
    if (prev == next) {
      memo[prev][next].push_back("A");
      return memo[prev][next];
    }
    
    pii from = pad_pos[prev];
    pii to = pad_pos[next];
    
    char UD = (from.first >= to.first) ? '^' : 'v';
    char LR = (from.second >= to.second) ? '<' : '>';
    
    string strUD = string(abs(from.first - to.first), UD);
    string strLR = string(abs(from.second - to.second), LR);
    string result = strUD + strLR;

    sort(begin(result), end(result));
    do {
      if (check_cmd(result, from)) {
	memo[prev][next].push_back(result + "A");
      }
    } while (next_permutation(begin(result), end(result)));

    return memo[prev][next];
  }
};

class NumPad : public KeyPad
{
public:
  NumPad()
  {
    pad.push_back("789");
    pad.push_back("456");
    pad.push_back("123");
    pad.push_back(" 0A");
    init();
  }
};

class DirPad : public KeyPad
{
public:
  DirPad()
  {
    pad.push_back(" ^A");
    pad.push_back("<v>");
    init();
  }
};

ostream &operator<<(ostream &os, pii p)
{
  return os << "(" << p.first << ", " << p.second << ")";
}


ll memo_move[256][256][30];

DirPad dirpad;

ll find_move(int prev, int next, int num_robot)
{
  if (memo_move[prev][next][num_robot]) {
    return memo_move[prev][next][num_robot];
  }
  
  vs cmd_list = dirpad.find_move(prev, next);

  if (num_robot == 1) {
    // last robot level so next level is human, just return the length
    return cmd_list[0].length();
  }

  ll best = LONG_LONG_MAX;
  for (auto cmd : cmd_list) {
    char cmd_prev = 'A';
    ll temp = 0;
    for (auto cmd_ch : cmd) {
      temp += find_move(cmd_prev, cmd_ch, num_robot-1);
      cmd_prev = cmd_ch;
    }
    best = min(best, temp);
  }

  return memo_move[prev][next][num_robot] = best;
}

ll complexity(string code)
{
  const int NUM_ROBOT = 25;
  NumPad numpad;

  ll ans = 0;
  char code_prev = 'A';
  for (auto code_ch : code) {
    vs cmd_list = numpad.find_move(code_prev, code_ch);
    ll best = LONG_LONG_MAX;

    for (auto cmd : cmd_list) {
      char cmd_prev = 'A';
      ll temp = 0;
      for (auto cmd_ch : cmd) {
	temp += find_move(cmd_prev, cmd_ch, NUM_ROBOT);
	cmd_prev = cmd_ch;
      }
      best = min(best, temp);
    }

    ans += best;
    code_prev = code_ch;
  }

  cout << "code = " << code << ": length = " << ans << endl;
  ans *= stoi(code.substr(0,3));
  return ans;
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
