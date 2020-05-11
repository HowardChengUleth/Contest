#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

struct State
{
  int Ca, Cb, A, B;

  State(int CCa, int CCb, int AA = 0, int BB = 0)
  {
    Ca = CCa;
    Cb = CCb;
    A = AA;
    B = BB;
  }

  State step(int op) const
  {
    int move;

    State s(*this);
    switch (op) {
    case 0:
      s.A = Ca;
      break;
    case 1:
      s.B = Cb;
      break;
    case 2:
      s.A = 0;
      break;
    case 3:
      s.B = 0;
      break;
    case 4:
      move = min(A, Cb-B);
      s.A = A - move;
      s.B = B + move;
      break;
    case 5:
      move = min(B, Ca-A);
      s.A = A + move;
      s.B = B - move;
      break;
    }
    return s;
  }

  bool target(int N) const
  {
    return B == N;
  }

  int to_int(void) const
  {
    return A*1001+B;
  }

  static string opstring(int op)
  {
    const string opnames[] = {
      "fill A", "fill B", "empty A", "empty B", "pour A B", "pour B A"
    };
    return opnames[op];
  }
};

struct Info
{
  int state_num;
  char op;

  Info()
  {
    state_num = op = -1;
  }

  Info(const State &s, char op)
  {
    state_num = s.to_int();
    this->op = op;
  }
};

void print_sol(Info *pred, int s)
{
  if (pred[s].op == -1) {
    return;
  }

  print_sol(pred, pred[s].state_num);
  cout << State::opstring(pred[s].op) << endl;
}

void solve(int Ca, int Cb, int N)
{
  const int v_size = 1001*1001;
  bool *visited = new bool[v_size];
  Info *pred = new Info[v_size];

  fill(visited, visited+v_size, false);

  queue<State> q;
  State start(Ca, Cb);

  q.push(start);
  visited[start.to_int()] = true;
  pred[start.to_int()] = Info(start, -1);

  State curr(Ca, Cb);
  while (!q.empty()) {
    curr = q.front();
    q.pop();
    if (curr.target(N)) {
      break;
    }

    for (int op = 0; op < 6; op++) {
      State next = curr.step(op);
      if (visited[next.to_int()]) continue;
      q.push(next);
      visited[next.to_int()] = true;
      pred[next.to_int()] = Info(curr, op);
    }
  }

  print_sol(pred, curr.to_int());
  cout << "success" << endl;
  delete[] visited;
  delete[] pred;
}

int main(void)
{
  int Ca, Cb, N;

  while (cin >> Ca >> Cb >> N) {
    solve(Ca, Cb, N);
  }
  return 0;
}
