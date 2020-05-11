#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <queue>

using namespace std;

struct Info
{
  string word;
  int index;
  char temp;

  Info(const string &w = "", int i = 0)
    : word(w), index(i), temp(' ') { }

  bool operator<(const Info &x) const
  {
    return word < x.word;
  }

  bool operator==(const Info &x) const
  {
    return word == x.word;
  }

  void change(int i)
  {
    if (0 <= i && i < word.length()) {
      swap(word[i], temp);
    }
  }
};

bool sortindex(const Info &x1, const Info &x2)
{
  return x1.index < x2.index;
}

const int MAX_WORDS = 25143;

string dict[MAX_WORDS];
Info info[MAX_WORDS];
int dict_size = 0;

list<int> G[MAX_WORDS];

void build_graph(void)
{
  for (int i = 0; i < dict_size; i++) {
    G[i].clear();
  }

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < dict_size; j++) {
      info[j].change(i);
    }
    sort(info, info + dict_size);
    for (int m = 0; m < dict_size; m++) {
      for (int n = m+1; n < dict_size && info[m].word == info[n].word; n++) {
	int u = info[m].index;
	int v = info[n].index;
	G[u].push_back(v);
	G[v].push_back(u);
      }
    }

    for (int j = 0; j < dict_size; j++) {
      info[j].change(i);
    }
  }
  sort(info, info + dict_size);
}

void BFS(const string &from, const string &to)
{
  // search backward
  int from_ind = equal_range(info, info + dict_size, Info(from)).first->index,
    to_ind = equal_range(info, info + dict_size, Info(to)).first->index;
    
  int next[MAX_WORDS];
  bool visited[MAX_WORDS];

  fill(next, next + dict_size, -1);
  fill(visited, visited + dict_size, false);

  queue<int> q;

  q.push(to_ind);
  visited[to_ind] = true;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    if (v == from_ind) {
      break;
    }
    for (list<int>::const_iterator it = G[v].begin(); it != G[v].end(); ++it) {
      int w = *it;
      if (!visited[w]) {
	next[w] = v;
	visited[w] = true;
	q.push(w);
      }
    }
  }

  if (!visited[from_ind]) {
    cout << "No solution." << endl;
  } else {
    do {
      cout << dict[from_ind] << endl;
      from_ind = next[from_ind];
    } while (from_ind != -1);
  }
}

int main(void)
{
  string w;

  while (getline(cin, w) && w != "") {
    dict[dict_size] = w;
    info[dict_size] = Info(w, dict_size);
    dict_size++;
  }

  build_graph();

  string from, to;
  bool first = true;
  while (cin >> from >> to) {
    if (!first) {
      cout << endl;
    }
    BFS(from, to);
    first = false;
  }
  return 0;
}
