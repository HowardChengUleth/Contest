#include <bits/stdc++.h>

using namespace std;

struct Message
{
  string from, to;

  // low = 0, high = 1
  int sig;

  Message(string f, string t, int s)
    : from{f}, to{t}, sig{s} { }

  void print() const {
    cout << from << " -" << sig << " -> " << to << endl;
  }
};

class Module
{
public:
  string name;
  vector<string> dest;

  void add_dest(string str)
  {
    dest.push_back(str);
  }

  virtual void add_input(string str)
  {

  }
  
  virtual void process(Message msg);
};

class Broadcast : public Module
{
public:
};

class FlipFlop : public Module
{
public:
  bool state = false;
  virtual void process(Message msg);
};

class Conjunction : public Module
{
public:
  map<string,int> input;
  virtual void process(Message msg);
  virtual void add_input(string str)
  {
    input[str] = 0;
  }
};

map<string, Module*> modules;

queue<Message> msgQ;

void Module::process(Message msg)
{  
  for (auto s : dest) {
    msgQ.emplace(name, s, msg.sig);
  }
}

void FlipFlop::process(Message msg)
{
  if (msg.sig) return;
  state = !state;
  msg.sig = state ? 1 : 0;
  Module::process(msg);
}

void Conjunction::process(Message msg)
{
  input[msg.from] = msg.sig;

  bool allhigh = true;
  for (auto [p, v] : input) {
    allhigh &= v != 0;
  }
  if (allhigh) {
    msg.sig = 0;
  } else {
    msg.sig = 1;
  }
  Module::process(msg);
}

void parse_module(string line)
{
  replace(begin(line), end(line), ',', ' ');
  istringstream iss(line);
  string name, dummy, dest;
  iss >> name >> dummy;

  Module *module;
  if (name[0] == '%') {
    module = new FlipFlop();
    name = name.substr(1);
  } else if (name[0] == '&') {
    module = new Conjunction();
    name = name.substr(1);
  } else {
    assert(name == "broadcaster");
    module = new Broadcast();
  }
  while (iss >> dest) {
    module->add_dest(dest);
  }

  module->name = name;
  modules[name] = module;
}

void connect_modules()
{
  for (auto [name, module] : modules) {
    for (auto s : module->dest) {
      if (modules[s] == nullptr) {
	modules[s] = new Module();
      }
      modules[s]->add_input(name);
    }
  }
}

typedef long long ll;

map<string,int> cycle_len;
vector<string> fedin{ "st", "tn", "hh", "dt" };

// turns out that rx is fed in by &lv, which is fed in by
// st, tn, hh, dt.  And these cycles in a very easy way.  They get high
// at k * cycle_len
void press_broadcast(int step)
{
  Message msg("button", "broadcaster", 0);
  msgQ.push(msg);
  while (!msgQ.empty()) {
    auto msg = msgQ.front();
    msgQ.pop();
    //    msg.print();

    if (step > 1 && msg.sig == 1 &&
	find(begin(fedin), end(fedin), msg.from) != end(fedin)) {
      if (cycle_len.find(msg.from) == cycle_len.end()) {
	cycle_len[msg.from] = step;
      }
    }
    
    modules[msg.to]->process(msg);
  }
  //  cout << "=====" << endl;
}

ll gcd(ll a, ll b)
{
  if (!b) return a;
  return gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
  ll g = gcd(a, b);
  return (a/g) * b;
}

int main()
{
  string line;
  while (getline(cin, line)) {
    parse_module(line);
  }
  connect_modules();

  for (int i = 0; ; i++) {
    press_broadcast(i+1);
    bool found = true;
    for (auto s : fedin) {
      if (cycle_len.find(s) == cycle_len.end()) {
	found = false;
      }
    }

    ll ans = 1;
    if (found) {
      for (auto [s, len] : cycle_len) {
	ans = lcm(ans, len);
      }
      cout << ans << endl;
      break;
    }
  }
  return 0;
}
