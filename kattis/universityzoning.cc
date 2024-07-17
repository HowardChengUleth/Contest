#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
typedef vector<pii> vpii;

struct Student
{
  ll D, f, r, c;

  void read()
  {
    cin >> r >> c >> D >> f;
    f--;
  }

  bool operator<(const Student &other) const
  {
    return D < other.D;
  }
};

ll R, C, F, S, G;
vpii faculty[100];
vector<Student> enrol[100];
ll T[100];

void read_faculty()
{
  for (int i = 0; i < F; i++) {
    int K;
    cin >> K;

    for (int j = 0; j < K; j++) {
      ll r, c;
      cin >> r >> c;
      faculty[i].emplace_back(r,c);
    }
    
    sort(begin(faculty[i]), end(faculty[i]));
  }
}

void read_student()
{
  for (int i = 0; i < S; i++) {
    Student s;
    s.read();
    enrol[s.f].push_back(s);
  }
}

void read_T()
{
  for (int i = 0; i < F; i++) {
    cin >> T[i];
  }
}

ll process_faculty(int i)
{
  sort(begin(enrol[i]), end(enrol[i]));

  // now collect all the distances
  vector<ll> distances;
  for (int k = 0; k < enrol[i].size(); k++) {
    Student &s = enrol[i][k];
    pii dest_pos = faculty[i][k];

    ll dist = abs(s.r - dest_pos.first) + abs(s.c - dest_pos.second);
    distances.push_back(dist);
  }

  sort(begin(distances), end(distances));
  return accumulate(begin(distances), begin(distances) + T[i], 0LL);
}

int main()
{
  cin >> R >> C >> F >> S >> G;
  
  read_faculty();
  read_student();
  read_T();

  vector<ll> faculty_ans;
  for (int i = 0; i < F; i++) {
    faculty_ans.push_back(process_faculty(i));
  }
  sort(begin(faculty_ans), end(faculty_ans));
  cout << accumulate(begin(faculty_ans), begin(faculty_ans) + G, 0LL) << endl;

  return 0;
}
