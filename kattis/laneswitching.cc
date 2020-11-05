#include <bits/stdc++.h>

using namespace std;

class UnionFind
{
      struct UF { int p; int rank; };

   public:
      UnionFind(int n) {          // constructor
	 howMany = n;
	 uf = new UF[howMany];
	 for (int i = 0; i < howMany; i++) {
	    uf[i].p = i;
	    uf[i].rank = 0;
	 }
      }

      ~UnionFind() {
         delete[] uf;
      }

      int find(int x) { return find(uf,x); }        // for client use
      
      bool merge(int x, int y) {
	 int res1, res2;
	 res1 = find(uf, x);
	 res2 = find(uf, y);
	 if (res1 != res2) {
	    if (uf[res1].rank > uf[res2].rank) {
	       uf[res2].p = res1;
	    }
	    else {
	       uf[res1].p = res2;
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


const int MAX_N = 100+1;

typedef pair<int,int> Interval;

int N, M, R;
vector<Interval> lane_cars[MAX_N], lane_gaps[MAX_N];
map<pair<int,Interval>,int> ID;
Interval acm_car;
int startID, endID;
double init_gap;

int read_car(Interval &car)
{
  int lane, len, dist;
  cin >> lane >> len >> dist;
  car = Interval{dist, min(R, dist+len)};
  return lane;
}

void read_input()
{
  cin >> N >> M >> R;

  // last lane is artificial
  N++;
  
  for (int i = 0; i < N; i++) {
    // add fake cars at the beginning and end
    lane_cars[i].push_back(Interval{0,0});
    lane_cars[i].push_back(Interval{R, R+1});
  }
  
  read_car(acm_car);
  for (int i = 1; i < M; i++) {
    Interval car;
    int lane = read_car(car);
    lane_cars[lane].push_back(car);
  }

  for (int i = 0; i < N; i++) {
    sort(lane_cars[i].begin(), lane_cars[i].end());
#ifdef DEBUG
    for (auto p : lane_cars[i]) {
      cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;
#endif
  }
}

int overlap(Interval gap1, Interval gap2)
{
  if (gap1 > gap2) swap(gap1, gap2);

  if (gap2.second <= gap1.second)
    return gap2.second - gap2.first;
  else
    return max(gap1.second - gap2.first, 0);
}

void compute_gaps()
{
  int num = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 1; j < (int)lane_cars[i].size(); j++) {
      assert(overlap(lane_cars[i][j-1], lane_cars[i][j]) == 0);
      Interval gap{lane_cars[i][j-1].second, lane_cars[i][j].first};
      lane_gaps[i].push_back(gap);
      ID[make_pair(i,gap)] = num++; 
 
      if (i == 0 && overlap(acm_car, gap) == overlap(acm_car, acm_car)) {
	startID = ID[make_pair(i,gap)];
	init_gap = min(acm_car.first - gap.first, gap.second - acm_car.second);
	assert(init_gap >= 0);
      }
      if (i == N-1) {
	endID = ID[make_pair(i,gap)];
      }
    }

#ifdef DEBUG 
    for (auto p : lane_gaps[i]) {
      cout << "(" << p.first << "," << p.second << "," << ID[make_pair(i,p)] << ") ";
    }
    cout << endl;
#endif
  }
}

typedef tuple<int,int,int> Edge;

void compute_safety()
{
  vector<Edge> elist;

  int acm_len = acm_car.second - acm_car.first;
  for (int i = 0; i < N-1; i++) {
    for (auto p : lane_gaps[i]) {
      for (auto q : lane_gaps[i+1]) {
	int t = overlap(p, q);
#ifdef DEBUG
	cout << ID[make_pair(i,p)] << "+" << ID[make_pair(i+1,q)] << "->"
	     << t << endl;
#endif
	Edge e{t-acm_len, ID[make_pair(i,p)], ID[make_pair(i+1,q)]};
	if (t-acm_len >= 0) {
	  elist.push_back(e);
	}
      }
    }
  }

  sort(elist.rbegin(), elist.rend());
#ifdef DEBUG
  cout << "======================" << endl;
  for (auto e : elist) {
    cout << "(" << get<0>(e) << ", " << get<1>(e) << ", " << get<2>(e) << ")"
	 << endl;
  }
#endif

  UnionFind uf(endID+1);
  int last = INT_MAX;
  for (int i = 0; i < (int)elist.size() &&
	 uf.find(startID) != uf.find(endID); i++) {
    Edge &e = elist[i];
    last = get<0>(e);
    uf.merge(get<1>(e), get<2>(e));
  }
  if (uf.find(startID) != uf.find(endID)) {
    cout << "Impossible" << endl;
  } else {
    double ans = last/2.0;
    cout << fixed << setprecision(6) << min(ans, init_gap) << endl;
  }
}

int main()
{
  read_input();
  compute_gaps();
  compute_safety();
  return 0;
}
