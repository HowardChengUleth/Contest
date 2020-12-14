#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

void partA(vector<string> cmd)
{
  map<ull,ull> mem;
  ull mask_and, mask_or;

  mask_or = 0;
  mask_and = 0xFFFFFFFFFFULL;
  for (auto s : cmd) {
    for (auto &c : s) {
      if (c == '[' || c == ']' || c == '=')
	c = ' ';
    }
    istringstream iss(s);

    string cmd, arg1, arg2;
    iss >> cmd >> arg1 >> arg2;
    if (cmd == "mask") {
      mask_or = 0;
      mask_and = 0xFFFFFFFFFFFFFFFFULL;
      for (int i = 0; i < arg1.length(); i++) {
	char ch = arg1[arg1.length()-1-i];
	if (ch == '1') {
	  mask_or |= (1ULL << i);
	} else if (ch == '0') {
	  mask_and -= (1ULL << i);
	}
      }
    } else if (cmd == "mem") {
      ull addr = stoll(arg1);
      ull val = ((ull)stoll(arg2) | mask_or) & mask_and;
      mem[addr] = val;
    }
  }

  ull ans = 0;
  for (auto p : mem) {
    ans += p.second;
  }

  cout << "A = " << ans << endl;
}

void write_mem(map<ull,ull> &mem, ull addr, ull val, string mask, int pos)
{
  if (pos == 36) {
    mem[addr] = val;
    return;
  }

  ull onmask = (1ULL << (35 - pos));
  ull offmask = 0xFFFFFFFFFFULL - onmask;
  switch (mask[pos]) {
  case '0':
    write_mem(mem, addr, val, mask, pos+1);
    break;
  case '1':
    write_mem(mem, addr | onmask, val, mask, pos+1);
    break;
  case 'X':
    write_mem(mem, addr | onmask, val, mask, pos+1);
    write_mem(mem, addr & offmask, val, mask, pos+1);
    break;
  }
}

void partB(vector<string> cmd)
{
  map<ull,ull> mem;
  string mask;

  for (auto s : cmd) {
    for (auto &c : s) {
      if (c == '[' || c == ']' || c == '=')
	c = ' ';
    }
    istringstream iss(s);

    string cmd, arg1, arg2;
    iss >> cmd >> arg1 >> arg2;
    if (cmd == "mask") {
      mask = arg1;
    } else if (cmd == "mem") {
      ull addr = stoll(arg1);
      ull val = stoll(arg2);
      write_mem(mem, addr, val, mask, 0);
    }
  }

  ull ans = 0;
  for (auto p : mem) {
    ans += p.second;
  }

  cout << "A = " << ans << endl;
}

int main()
{
  vector<string> cmd;
  string line;

  while (getline(cin, line)) {
    cmd.push_back(line);
  }

  partA(cmd);
  partB(cmd);
  
  return 0;
}
