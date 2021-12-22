#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool inside(int c)
{
  return (-50 <= c && c <= 50);
}

bool outside(int x1, int x2, int y1, int y2, int z1, int z2)
{
  return !(inside(x1) && inside(x2) && inside(y1) && inside(y2)
	   && inside(z1) && inside(z2));
}

bool A[101][101][101];

struct Cube
{
  bool on;
  int x1, x2, y1, y2, z1, z2;
  Cube(int xx1, int xx2, int yy1, int yy2, int zz1, int zz2, string cmd)
    : x1(xx1), x2(xx2), y1(yy1), y2(yy2), z1(zz1), z2(zz2)
  {
    on = (cmd == "on");
  }
};

vector<Cube> ocube;

void insert(set<int> &S, int x)
{
  S.insert(x-1);
  S.insert(x);
  S.insert(x+1);
}
	    
int main()
{
  string cmd, line;
  while (cin >> cmd) {
    getline(cin, line);
    replace(begin(line), end(line), ',', ' ');
    replace(begin(line), end(line), '.', ' ');
    replace(begin(line), end(line), '=', ' ');

    istringstream iss(line);
    char ch;
    int x1, x2, y1, y2, z1, z2;
    iss >> ch >> x1 >> x2 >> ch >> y1 >> y2 >> ch >> z1 >> z2;

    ocube.emplace_back(x1, x2, y1, y2, z1, z2, cmd);
  }

  set<int> xset, yset, zset;
  
  for (auto c : ocube) {
    insert(xset, c.x1);
    insert(xset, c.x2);
    insert(yset, c.y1);
    insert(yset, c.y2);
    insert(zset, c.z1);
    insert(zset, c.z2);
  }

  map<int,int> xindex, yindex, zindex;
  map<int,int> xinv, yinv, zinv;
  int k = 0;
  for (auto x : xset) {
    //    cout << "x = " << x << " -> " << k << endl;
    xinv[k] = x;
    xindex[x] = k++;
  }
  xinv[k] = xinv[k-1]+1;
  
  k = 0;
  for (auto y : yset) {
    //    cout << "y = " << y << " -> " << k << endl;
    yinv[k] = y;
    yindex[y] = k++;
  }
  yinv[k] = yinv[k-1]+1;
  
  k = 0;
  for (auto z : zset) {
    //    cout << "z = " << z << " -> " << k << endl;
    zinv[k] = z;
    zindex[z] = k++;
  }
  zinv[k] = zinv[k-1]+1;

  int D1 = xset.size();
  int D2 = yset.size();
  int D3 = zset.size();

  vector<vector<vector<bool>>> G(D1);
  for (auto &v : G) {
    v.resize(D2);
    for (auto &w : v) {
      w.resize(D3, false);
    }
  }
  cout << "D1, D2, D3 = " << D1 << ' ' << D2 << ' ' << D3 << endl;

  int ci = 0;
  for (auto c : ocube) {
    cout << "Cube " << ++ci << endl;
    int xi1 = xindex[c.x1], xi2 = xindex[c.x2];
    int yi1 = yindex[c.y1], yi2 = yindex[c.y2];
    int zi1 = zindex[c.z1], zi2 = zindex[c.z2];

    /*
    if (c.on) {
      cout << "Turning on" << endl;
    } else {
      cout << "Turning off" << endl;
      }
    */
    for (int x = xi1; x <= xi2; x++) {
      for (int y = yi1; y <= yi2; y++) {
	for (int z = zi1; z <= zi2; z++) {
	  G[x][y][z] = c.on;
	}
      }
    }
    //    cout << "===============" << endl;
  }

  cout << "here" << endl;
  ll ans = 0;
  for (int x = 0; x < D1; x++) {
    cout << "x = " << x << endl;
    for (int y = 0; y < D2; y++) {
      for (int z = 0; z < D3; z++) {
	if (G[x][y][z]) {
	  ll dx = xinv[x+1] - xinv[x];
	  ll dy = yinv[y+1] - yinv[y];
	  ll dz = zinv[z+1] - zinv[z];
	  ans += dx * dy * dz;
	}
      }
    }
  }
    
  
  cout << ans << endl;

  return 0;
}
