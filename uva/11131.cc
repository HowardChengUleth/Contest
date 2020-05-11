#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;

const int MAX_N = 5000;
const int MAX_PARENT = 10;

int num_names = 0;
int num_parent[MAX_N];
int parent[MAX_N][MAX_PARENT];

vector< list<int> > traverse(int root)
{
  vector< list<int> > out, p[MAX_PARENT];
  list<int> l;

  for (int i = 0; i < num_parent[root]; i++) {
    p[i] = traverse(parent[root][i]);
  }

  if (!num_parent[root]) {
    l.push_back(root);
    out.push_back(l);
    return out;
  }

  if (num_parent[root] == 1) {
    out = p[0];
    for (unsigned int i = 0; i < out.size(); i++) {
      out[i].push_back(root);
    }
    return out;
  }

  for (int i = 0; i < num_parent[root]; i++) {
    if (p[i].size() == 1) {
      p[i].push_back(p[i][0]);
    }
    l.splice(l.begin(), p[i][0]);
  }
  l.push_back(root);
  out.push_back(l);

  list<int> l2;
  for (int i = num_parent[root]-1; i >= 0; i--) {
    l2.splice(l2.begin(), p[i][1]);
  }
  l2.push_back(root);
  out.push_back(l2);
  
  return out;
}

int main(void)
{
  map<string,int> index;
  string names[MAX_N];
  int child, p;
  string s, t;
  unsigned int pos;
  int prev;

  while (getline(cin, s)) {
    prev = 0;
    pos = s.find(',', prev);
    if (pos != string::npos) {
      t = s.substr(prev, pos-prev);
      if (index.find(t) == index.end()) {
	names[num_names] = t;
	index[t] = num_names++;
      }
      child = index[t];
      prev = pos+1;
    } else {
      names[num_names] = s;
      index[s] = num_names++;
      continue;
    }

    while ((pos = s.find(',', prev)) != string::npos) {
      t = s.substr(prev, pos-prev);
      if (index.find(t) == index.end()) {
	names[num_names] = t;
	index[t] = num_names++;
      }
      p = index[t];
      prev = pos+1;
      parent[child][num_parent[child]++] = p;
    }
    
    t = s.substr(prev, s.length()-prev);
    if (index.find(t) == index.end()) {
      names[num_names] = t;
      index[t] = num_names++;
    }
    p = index[t];
    parent[child][num_parent[child]++] = p;
  }

  vector< list<int> > out = traverse(0);
  cout << out.size() << endl << endl;

  for (unsigned int i = 0; i < out.size(); i++) {
    if (i) cout << endl;
    for (list<int>::iterator it = out[i].begin(); it != out[i].end(); ++it) {
      cout << names[*it] << endl;
    }
  }

  return 0;
}
