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
ll lo = 0, hi = 0;

void press_broadcast()
{
  Message msg("button", "broadcaster", 0);
  msgQ.push(msg);
  while (!msgQ.empty()) {
    auto msg = msgQ.front();
    msgQ.pop();
    //    msg.print();

    if (msg.sig) {
      hi++;
    } else {
      lo++;
    }
    
    modules[msg.to]->process(msg);
  }
  //  cout << "=====" << endl;
}

int main()
{
  string line;
  while (getline(cin, line)) {
    parse_module(line);
  }
  connect_modules();

  const int TIMES = 1000;
  for (int i = 0; i < TIMES; i++) {
    press_broadcast();
  }
  cout << "lo = " << lo << endl;
  cout << "hi = " << hi << endl;
  cout << lo*hi << endl;
  return 0;
}
