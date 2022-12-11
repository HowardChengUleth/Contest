#include <bits/stdc++.h>

using namespace std;

struct Monkey
{
  deque<int> items;
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
      items.push_back(x);
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
  }

  void print() const
  {
    if (ID == -1) return;
    cout << ID << ": ";
    for (auto x : items) {
      cout << x << ' ';
    }
    cout << endl;
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
    int old = items.front();
    items.pop_front();
    inspect++;
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

    old /= 3;
    if (old % mod == 0) {
      monkey[dest[1]].items.push_back(old);
    } else {
      monkey[dest[0]].items.push_back(old);
    }
  }
}

int main()
{
  for (int i = 0; i < 8; i++) {
    monkey[i].read();
  }

  for (int round = 0; round < 20; round++) {
    for (int i = 0; i < 8; i++) {
      monkey[i].process();
    }
    /*
    cout << "round " << round+1 << ":" << endl;
    for (int i = 0; i < 8; i++) {
      monkey[i].print();
    }
    */
  }

  priority_queue<int> pq;
  for (int i = 0; i < 8; i++) {
    if (monkey[i].ID != -1) {
      pq.push(monkey[i].inspect);
    }
  }

  int ans = pq.top();  pq.pop();
  ans *= pq.top();  pq.pop();

  cout << ans << endl;


  return 0;
}
