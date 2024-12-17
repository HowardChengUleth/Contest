#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef long long ll;

ll A, B, C;

ll literal(ll x)
{
  return x;
}

ll combo(ll x)
{
  if (0 <= x && x <= 3)
    return x;
  else if (x == 4) 
    return A;
  else if (x == 5)
    return B;
  else if (x == 6)
    return C;

  assert(false);
  return -1;
}

typedef vector<int> vi;
vi output;

int pc = 0;
bool printed = false;

void adv(int arg)
{
  ll num = A;

  assert(combo(arg) <= 63);
  
  ll den = (1LL << combo(arg));
  A = num / den;
}

void bxl(int arg)
{
  B ^= literal(arg);
}

void bst(int arg)
{
  B = combo(arg) & 0x7;
}

bool jnz(int arg)
{
  if (A == 0)
    return false;
  pc = literal(arg);
  return true;
}

void bxc(int arg)
{
  B ^= C;
}

void out(int arg)
{
  output.push_back(combo(arg) & 0x7);
}

void bdv(int arg)
{
  ll num = A;

  assert(combo(arg) <= 63);
  
  ll den = (1LL << combo(arg));
  B = num / den;
}

void cdv(int arg)
{
  ll num = A;

  assert(combo(arg) <= 63);
  
  ll den = (1LL << combo(arg));
  C = num / den;
}

ll read_reg()
{
  string s;
  cin >> s >> s;

  ll x;
  cin >> x;
  return x;
}


vi read_prog()
{
  string s;
  cin >> s >> s;

  replace(begin(s), end(s), ',', ' ');
  istringstream iss(s);
  vi prog;
  int x;
  while (iss >> x) {
    prog.push_back(x);
  }
  return prog;
}

bool run_prog(vi prog, ll initA)
{
  A = initA;
  pc = 0;
  output.clear();
  
  while (pc < prog.size()) {
    if (output.size() > prog.size()) {
      return false;
    }
    
    int arg = prog[pc+1];
    switch(prog[pc]) {
    case 0:
      adv(arg);
      pc += 2;
      break;
    case 1:
      bxl(arg);
      pc += 2;
      break;
    case 2:
      bst(arg);
      pc += 2;
      break;
    case 3:
      if (!jnz(arg)) {
	pc += 2;
      }
      break;
    case 4:
      bxc(arg);
      pc += 2;
      break;
    case 5:
      out(arg);
      pc += 2;
      break;
    case 6:
      bdv(arg);
      pc += 2;
      break;
    case 7:
      cdv(arg);
      pc += 2;
      break;
    }
  }

  if (output.size() != prog.size()) {
    return false;
  }
  return equal(begin(output), end(output), begin(prog));
}

int main()
{
  A = read_reg();
  B = read_reg();
  C = read_reg();

  vi prog = read_prog();

  int Aval = 0;
  while (!run_prog(prog, Aval)) {
    Aval++;
  }

  cout << Aval << endl;

  return 0;
}
