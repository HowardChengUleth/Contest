#include <bits/stdc++.h>

using namespace std;

// UnionFind class -- based on Howard Cheng's C code for UnionFind
// Modified to use C++ by Rex Forsyth, Oct 22, 2003
//
// Constuctor -- builds a UnionFind object of size n and initializes it
// find -- return index of x in the UnionFind
// merge -- updates relationship between x and y in the UnionFind


class UnionFind
{
  struct UF { int p; int rank; int crew; int ship;};

public:
  UnionFind(int n) {          // constructor
    howMany = n;
    uf = new UF[howMany];
    for (int i = 0; i < howMany; i++) {
      uf[i].p = i;
      uf[i].rank = 0;
      uf[i].crew = uf[i].ship = 0;
    }
  }

  ~UnionFind() {
    delete[] uf;
  }

  void set(int x, int crew, int ship)
  {
    uf[x].crew = crew;
    uf[x].ship = ship;
  }
  
  int find(int x) { return find(uf,x); }        // for client use
  int crew(int x) {
    return uf[find(uf, x)].crew;
  }
  int ship(int x) {
    return uf[find(uf, x)].ship;
  }
  bool merge(int x, int y) {
    int res1, res2;
    res1 = find(uf, x);
    res2 = find(uf, y);
    if (res1 != res2) {
      if (uf[res1].rank > uf[res2].rank) {
	uf[res2].p = res1;
	uf[res1].crew += uf[res2].crew;
	uf[res1].ship += uf[res2].ship;
      }
      else {
	uf[res1].p = res2;
	uf[res2].crew += uf[res1].crew;
	uf[res2].ship += uf[res1].ship;
	if (uf[res1].rank == uf[res2].rank) {
	  uf[res2].rank++;
	}
      }
      return true;
    }
    return false;
  }
      
private:
  int howMany;
  UF* uf;

  int find(UF uf[], int x) {     // recursive funcion for internal use
    if (uf[x].p != x) {
      uf[x].p = find(uf, uf[x].p);
    }
    return uf[x].p;
  }
};

const int MAX_N = 100000;
UnionFind uf(2*MAX_N);
vector<bool> infight(2*MAX_N, false);
vector<int> crew(2*MAX_N, 0), ship(2*MAX_N, 0);

map<string,int> nameindex;
int name2index(const string &s)
{
  if (nameindex.find(s) == nameindex.end()) {
    int t = nameindex.size();
    return nameindex[s] = t;
  }
  return nameindex[s];
}

void do_u()
{
  string x, y;
  cin >> x >> y;
  int ix = name2index(x), iy = name2index(y);
  uf.merge(ix, iy);
}

void do_a()
{
  string x, y;
  cin >> x >> y;
  int ix = name2index(x), iy = name2index(y);
  if (uf.find(ix) == uf.find(iy)) {
    cout << "Aye" << endl;
  } else {
    cout << "Nay" << endl;
  }
}

void do_j()
{
  string x;
  int i, k;
  cin >> x >> i >> k;
  int ix = name2index(x);
  uf.set(ix, i, k);
  infight[ix] = true;
  crew[ix] = i;
  ship[ix] = k;
}

void do_s()
{
  string x;
  cin >> x;
  int ix = name2index(x);
  cout << uf.crew(ix) << endl;
}

void do_w()
{
  for (auto [s, i] : nameindex) {
    if (infight[i]) {
      cout << s << endl;
    }
  }
}

void remove(int index)
{
  infight[index] = false;

  int group = uf.find(index);
  int totalcrew = uf.crew(group);
  int totalship = uf.ship(group);
  uf.set(group, totalcrew - crew[index], totalship - ship[index]);

}

void do_r()
{
  string x, y;
  cin >> x >> y;
  int ix = name2index(x), iy = name2index(y);
  if (uf.find(ix) == uf.find(iy)) {
    cout << "Ye be a daft one! They be sailin' under the same flag!" << endl;
    return;
  }
  
  pair<int,int> xx(uf.crew(ix), uf.ship(ix)),
    yy(uf.crew(iy), uf.ship(iy));
  bool elimx = (xx <= yy);
  bool elimy = (yy <= xx);

  if (elimx) {
    remove(ix);
  }
  if (elimy) {
    remove(iy);
  }

  if (xx > yy) {
    cout << x << endl;
  } else if (xx < yy) {
    cout << y << endl;
  } else {
    cout << "Arrr, both of them pirate crews be walkin' the plank!" << endl;
  }
  
}

int main()
{
  int n;
  cin >> n;

  while (n--) {
    char cmd;
    cin >> cmd;

    switch (cmd) {
    case 'u':
      do_u();
      break;
    case 'a':
      do_a();
      break;
    case 'j':
      do_j();
      break;
    case 's':
      do_s();
      break;
    case 'w':
      do_w();
      break;
    case 'r':
      do_r();
      break;
    }
  }

  return 0;
}
