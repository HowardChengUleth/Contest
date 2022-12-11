#include <bits/stdc++.h>

using namespace std;

struct Item
{
  vector<int> val;
  Item(int V)
  {
    val.resize(8);
    for (auto &x : val) {
      x = V;
    }
  }
};

int divisor[8] = {1,1,1,1,1,1,1,1};

struct Monkey
{
  deque<Item> items;
  int ID;
  char op;
  int val;
  int mod;

  int dest[2];

  int inspect;

  Monkey()
    : ID{-1}, inspect{0} { }
  
  void read()
  {
    string line;

    // ID
    cin >> line >> ID >> line;
    if (!cin) return;

    // items
    cin >> line >> line;
    getline(cin, line);
    replace(begin(line), end(line), ',', ' ');
    istringstream iss(line);
    int x;
    while (iss >> x) {
      items.emplace_back(x);
    }
    cin >> line >> line >> line >> line >> op >> line;
    if (line == "old") {
      op = '^';
      val = 2;
    } else {
      val = stoi(line);
    }
    cin >> line >> line >> line >> mod;
    cin >> line >> line >> line >> line >> line >> dest[1];
    cin >> line >> line >> line >> line >> line >> dest[0];

    divisor[ID] = mod;
  }

  void print() const
  {
    if (ID == -1) return;
    cout << ID << ": " << inspect << endl;
    /*    
    for (auto x : items) {
      cout << x << ' ';
    }
    cout << endl;
    */
    /*
    cout << op << ' ' << val << endl;
    cout << mod << endl;
    cout << dest[1] << ' ' << dest[0] << endl;
    */
  }

  void process();
};

Monkey monkey[8];

void Monkey::process()
{
  while (!items.empty()) {
    auto vec = items.front();
    items.pop_front();
    inspect++;
    for (int i = 0; i < 8; i++) {
      auto &old = vec.val[i]; 
      switch (op) {
      case '+':
	old += val;
	break;
      case '*':
	old *= val;
	break;
      case '^':
	old *= old;
	break;
      }
      old %= divisor[i];
    }

    //    old /= 3;
    int to;
    if (vec.val[ID] % mod == 0) {
      to = dest[1];
    } else {
      to = dest[0];
    }
    monkey[to].items.push_back(vec);
  }
}

int main()
{
  for (int i = 0; i < 8; i++) {
    monkey[i].read();
  }

  for (int round = 0; round < 10000; round++) {
    for (int i = 0; i < 8; i++) {
      monkey[i].process();
    }

    /*
    if (round == 0 || round == 19 || (round + 1) % 1000 == 0) {
      cout << "round " << round+1 << ":" << endl;
      for (int i = 0; i < 8; i++) {
	monkey[i].print();
      }
    }
    */
  }

  priority_queue<int> pq;
  for (int i = 0; i < 8; i++) {
    if (monkey[i].ID != -1) {
      pq.push(monkey[i].inspect);
    }
  }

  long long ans = pq.top();  pq.pop();
  ans *= pq.top();  pq.pop();

  cout << ans << endl;


  return 0;
}
