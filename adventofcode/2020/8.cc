#include <bits/stdc++.h>

using namespace std;

vector<pair<string,int>> cmd;

bool termend(int &acc)
{
  set<int> visited;
  int pc = 0;

  acc = 0;
  while (true) {
    if (pc >= cmd.size()) {
      return true;
    }

    if (visited.count(pc)) {
      return false;
    }
    
    visited.insert(pc);
    if (cmd[pc].first == "nop") {
      pc++;
    } else if (cmd[pc].first == "acc") {
      acc += cmd[pc].second;
      pc++;
    } else {
      pc += cmd[pc].second;
    }
  }
}

int main()
{
  string s;
  int a;
  while (cin >> s >> a) {
    cmd.emplace_back(s, a);
  }

  int acc;
  termend(acc);
  cout << "A = " << acc << endl;

  for (auto &p : cmd) {
    if (p.first == "nop") {
      p.first = "jmp";
    } else if (p.first == "jmp") {
      p.first = "nop";
    } else {
      continue;
    }

    if (termend(acc)) {
      cout << "B = " << acc << endl;
      break;
    }
    if (p.first == "nop") {
      p.first = "jmp";
    } else if (p.first == "jmp") {
      p.first = "nop";
    }
  }
  return 0;
}

