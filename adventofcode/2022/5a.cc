#include <bits/stdc++.h>

using namespace std;

vector<stack<char>> S;
int num_stacks;

void read_stacks()
{
  vector<string> lines;
  string line;
  while (getline(cin, line) && line != "") {
    lines.push_back(line);
  }

  string last = lines.back();
  lines.pop_back();

  num_stacks = (last.length() + 1) / 4;
  S.resize(num_stacks);

  for (auto it = rbegin(lines); it != rend(lines); ++it) {
    int len = it->length();
    for (int i = 0; i < num_stacks; i++) {
      int pos = 1 + i * 4;
      if (pos < len && (*it)[pos] != ' ') {
	S[i].push((*it)[pos]);
      }
    }
  }
}

void process()
{
  string cmd, from, to;
  int crates;
  int start, end;
  while (cin >> cmd >> crates >> from >> start >> to >> end) {
    start--;
    end--;
    for (int i = 0; i < crates; i++) {
      char ch = S[start].top();
      S[start].pop();
      S[end].push(ch);
    }
  }
}

int main()
{
  read_stacks();
  process();

  for (int i = 0; i < num_stacks; i++) {
    cout << S[i].top();
  }
  cout << endl;

  return 0;
}
