#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <cassert>
#include <queue>

using namespace std;

#include <map>
#include <string>

const int SRC = 0;
const int SINK = 1;

struct Edge
{
  int to_lang;
  int len;
  char first;

  Edge(int to = 0, int l = 0, char f = 'a')
    : to_lang(to), len(l), first(f)
  {
  }

};

struct Lang
{
  vector<Edge> nbrs;
  void clear()
  {
    nbrs.clear();
  }

  void addEdge(int to, const string &word)
  {
    nbrs.push_back(Edge(to, word.length(), word[0]));
  }
};

int node_index(int lang_i, char ch)
{
  return lang_i * 26 + (ch - 'a');
}

void index_node(int index, int &lang_i, char &ch)
{
  lang_i = index / 26;
  ch = (index % 26) + 'a';
}

int lang_index(map<string, int> &lindex, const string &lang)
{
  map<string, int>::iterator it = lindex.find(lang);
  if (it == lindex.end()) {
    int s = lindex.size();
    return lindex[lang] = s;
  } else {
    return it->second;
  }
}

Lang lang[4000];
int dist[4000*26];
bool done[4000*26];

void do_case(int m)
{
  map<string, int> lindex;

  for (int i = 0; i < 2*m; i++) {
    lang[i].clear();
  }
	 
  string lang1, lang2;
  cin >> lang1 >> lang2;
  int start = lang_index(lindex, lang1);
  int end = lang_index(lindex, lang2);
  
  for (int i = 0; i < m; i++) {
    int u, v;
    string word;
    cin >> lang1 >> lang2 >> word;
    u = lang_index(lindex, lang1);
    v = lang_index(lindex, lang2);
    lang[u].addEdge(v, word);
    lang[v].addEdge(u, word);
  }

  // do dijkstra
  priority_queue< pair<int, int> > fringe;
  fill(dist, dist + lindex.size() * 26, -1);
  fill(done, done + lindex.size() * 26, false);
  for (char ch = 'a'; ch <= 'z'; ch++) {
    int index = node_index(start, ch);
    dist[index] = 0;
    fringe.push(make_pair(-dist[index], index));
  }

  while (!fringe.empty()) {
    pair<int, int> next = fringe.top();
    fringe.pop();
    if (done[next.second]) continue;
    done[next.second] = true;

    int lang_i;
    char ch;
    index_node(next.second, lang_i, ch);

    if (lang_i == end) {
      cout << dist[next.second] << endl;
      return;
    }
    
    for (vector<Edge>::const_iterator it = lang[lang_i].nbrs.begin();
	 it != lang[lang_i].nbrs.end(); ++it) {
      const Edge &e = *it;
      if (e.first == ch) continue;
      int t_dist = -next.first + e.len;
      int to_index = node_index(e.to_lang, e.first);
      if (dist[to_index] == -1 || t_dist < dist[to_index]) {
	dist[to_index] = t_dist;
	fringe.push(make_pair(-dist[to_index], to_index));
      }
    }
  }
  
  cout << "impossivel" << endl;
}


int main(void)
{
  int m;
  while (cin >> m && m > 0) {
    do_case(m);
  }
  return 0;
}

