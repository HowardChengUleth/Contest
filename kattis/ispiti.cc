#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200000;

// RMQ:
//   call constructRMQ to get data structure M                   O(n)
//   call getmax to get the maximum from [a..b] inclusive        O(log n)
//     returns a pair of the form (maximum value,index of maximum value)
//   call update to change a value in the array                  O(log n)
typedef int Type;             // Change this as needed
const Type oo = INT_MIN;      // Change to INT_MAX for min.

typedef pair<Type,int> pti;
const pti p_oo = make_pair(oo,-1);
int Size;

void constructRMQ(Type A[MAX_N], pti M[4*MAX_N], int n) {
  Size = 1; while(Size < n) Size <<= 1;
  for (int i=0; i < Size; i++) M[Size-1+i] = (i < n ? make_pair(A[i],i) : p_oo);
  for (int i=Size-2; i>=0; i--) M[i] = max(M[2*i+1],M[2*i+2]);
}

pti getmax(pti M[4*MAX_N], int a, int b, int st=0,int en=Size,int ind=0) {
  if (a > b || a >= en || b < st)         return p_oo;
  if ((a <= st && en <= b) || st+1 >= en) return M[ind];
  int mid = (st+en)/2;
  return max(getmax(M,a,b,st,mid,2*ind+1), getmax(M,a,b,mid,en,2*ind+2));
}

void update(Type A[MAX_N], pti M[4*MAX_N], int i, Type val){
  A[i] = val; M[i += Size-1] = make_pair(val,i);
  while((i = (i-1)/2)) M[i] = max(M[2*i+1],M[2*i+2]);
}

Type A[MAX_N];
pti M[4*MAX_N];

struct Entry
{
  char type;
  int param[2];

  void read()
  {
    cin >> type;
    cin >> param[0];
    if (type == 'D') {
      cin >> param[1];
    }
  }
};


int N;
Entry entry[MAX_N];
vector<int> Bvals;
map<int,int> Bindex;
vector<set<pair<int,int>>> S;
vector<pair<int,int>> student;

int main()
{
  cin >> N;

  Bvals.reserve(N);
  student.reserve(N);
  for (int i = 0; i < N; i++) {
    entry[i].read();
    if (entry[i].type == 'D') {
      Bvals.push_back(entry[i].param[1]);
      student.emplace_back(entry[i].param[0], entry[i].param[1]);
    }
  }
  sort(begin(Bvals), end(Bvals));
  Bvals.resize(unique(begin(Bvals), end(Bvals)) - begin(Bvals));
  for (int i = 0; i < Bvals.size(); i++) {
    Bindex[Bvals[i]] = i;
  }
  int Bsize = Bindex.size();
  
  constructRMQ(A, M, Bsize);
  S.resize(Bsize);

  int sid = 0;
  int qid = 0;
  for (int i = 0; i < N; i++) {
    switch (entry[i].type) {
    case 'D':
      {
	int AA = entry[i].param[0], Bi = Bindex[entry[i].param[1]];
	int val = max(AA, A[Bi]);
	update(A, M, Bi, val);
	S[Bi].emplace(AA, ++sid);
      }
      break;
    case 'P':
      {
	qid++;
	int ii = entry[i].param[0]-1;
	int AA = student[ii].first, Bi = Bindex[student[ii].second];
	int lo = Bi+1, hi = Bsize-1;
	if (A[Bi] > AA) {
	  auto it = S[Bi].upper_bound(make_pair(AA, 2*MAX_N));
	  cout << it->second << endl;
	} else if (lo > hi || getmax(M, lo, hi).first < AA) {
	  cout << "NE" << endl;
	} else {
	  while (lo < hi) {
	    int mid = (lo+hi)/2;
	    if (getmax(M, lo, mid).first >= AA) {
	      hi = mid;
	    } else {
	      lo = mid+1;
	    }
	  }

	  auto it = S[lo].upper_bound(make_pair(AA,2*MAX_N));
	  if (it == S[lo].end()) {
	    --it;
	  }
	  auto it2 = it;
	  if (it2 != S[lo].begin()) {
	    --it2;
	  }
	  if (it2->first >= AA) {
	    it = it2;
	  }
	  cout << it->second << endl;
	}
      }
      break;
    }

  }

  return 0;
}
