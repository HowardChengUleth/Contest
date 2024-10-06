#include <bits/stdc++.h>

using namespace std;

// do BFS in the state space...state is just where the worm is.  The
// number of states: 100 positions for the head, next segment can be
// in one of 4 positions, and then each of the next segments can be in
// one of 3 positions.  So at most 100 * 4 * 3^14 = 1.9 billion...that's
// too much.  But many of these states would not be reachable...exactly
// how many states there are is a bit hard to tell...
typedef pair<int,int> pii;
typedef deque<pii> Snake;

int R, C;
vector<string> A;

pii apple;

void form_snake(Snake &snake)
{
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (A[i][j] == 'A') {
	apple = pii(i, j);
      } else if (isalnum(A[i][j])) {
	int k;
	if (isdigit(A[i][j])) {
	  k = A[i][j] - '0';
	} else {
	  k = A[i][j] - 'a' + 10;
	}
	if (k >= snake.size()) {
	  snake.resize(k+1);
	}
	snake[k] = pii(i, j);
      }
    }
  }
}

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

bool inside(pii p)
{
  auto [r, c] = p;
  return 0 <= r && r < R && 0 <= c && c < C;
}

bool can_move(const Snake &snake, int dir)
{
  auto head = snake[0];
  head.first += dr[dir];
  head.second += dc[dir];

  // cannot go outside
  if (!inside(head))
    return false;

  // cannot go backwards
  if (snake.size() > 1 && head == snake[1])
    return false;

  // cannot touch anything else except last one
  for (int i = 2; i < snake.size()-1; i++) {
    if (head == snake[i]) {
      return false;
    }
  }

  return true;
}

Snake move_snake(const Snake &snake, int dir)
{
  Snake res = snake;
  auto head = res[0];
  res.pop_back();

  head.first += dr[dir];
  head.second += dc[dir];
  res.push_front(head);
  return res;
}

void print_snake(const Snake &s)
{
  for (auto [r, c] : s) {
    cout << "(" << r << ", " << c << ") ";
  }
  cout << endl;
}

void BFS(const Snake &snake)
{
  set<Snake> visited;
  queue<Snake> Q;

  Q.push(snake);
  visited.insert(snake);

  while (!Q.empty()) {
    auto curr = Q.front();
    Q.pop();

    for (int dir = 0; dir < 4; dir++) {
      if (!can_move(curr, dir)) {
	continue;
      }

      auto next = move_snake(curr, dir);
      if (next[0] == apple) {
	cout << 1 << endl;
	return;
      }
      if (visited.count(next) == 0) {
	visited.insert(next);
	Q.push(next);
      }
    }
  }

  cout << 0 << endl;
}

int main()
{
  cin >> R >> C;
  A.resize(R);
  for (auto &s : A) {
    cin >> s;
  }

  deque<pii> snake;
  form_snake(snake);

  BFS(snake);

  return 0;
}
