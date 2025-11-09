#include <bits/stdc++.h>

using namespace std;

int N, Q;

struct Team
{
  string name;
  int balls;
};

vector<Team> team;
int total_balls;

double pre2, pre3;

// prob1[i] = probability that team i gets first draw
vector<double> prob1;

// prob2[i][j] = probability that teams i and j get first 2 draws
vector<vector<double>> prob2;

// prob3[i][j][k] = probability that teams i, j, k get the first 3 draws
vector<vector<vector<double>>> prob3;

void precompute()
{
  total_balls = 0;
  for (int i = 0; i < N; i++) {
    total_balls += team[i].balls;
  }
  
  prob1.resize(N);
  for (int i = 0; i < N; i++) {
    prob1[i] = double(team[i].balls) / total_balls;
  }

  // compute probability for first 2 draws
  if (N < 2)
    return;
  
  prob2.resize(N, vector<double>(N, 0.0));
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      double p = 0.0;

      // get i and then j
      p += prob1[i] * double(team[j].balls) / (total_balls - team[i].balls);

      // j then i
      p += prob1[j] * double(team[i].balls) / (total_balls - team[j].balls);

      prob2[i][j] = prob2[j][i] = p;
    }
  }

  // compute probability for first 3 draws
  if (N < 3)
    return;
  
  prob3.resize(N);
  for (int i = 0; i < N; i++) {
    prob3[i].resize(N, vector<double>(N, 0.0));
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
	if (i == j || i == k || j == k) continue;
	double p = 0.0;

	// j,k then i
	p += prob2[j][k] * double(team[i].balls) /
	  (total_balls - team[j].balls - team[k].balls);
	
	// i,k then j
	p += prob2[i][k] * double(team[j].balls) /
	  (total_balls - team[i].balls - team[k].balls);
	
	// i,j then k
	p += prob2[i][j] * double(team[k].balls) /
	  (total_balls - team[i].balls - team[j].balls);

	prob3[i][j][k] = p;
      }
    }
  }
}

double answer(int ti, int k)
{
  double total = 0.0;

  // get it in the 1st draw
  total += prob1[ti];

  // get it in the 2nd draw
  if (k >= 2) {
    for (int j = 0; j < N; j++) {
      if (j == ti) continue;
      total += prob1[j] * double(team[ti].balls) / (total_balls - team[j].balls);
    }
  }
  
  // get it in the 3rd draw
  if (k >= 3) {
    for (int i = 0; i < N; i++) {
      if (i == ti) continue;
      for (int j = i+1; j < N; j++) {
	if (j == ti) continue;
	total += prob2[i][j] * double(team[ti].balls) /
	  (total_balls - team[i].balls - team[j].balls);
      }
    }
  }

  // get it in one of the remaining k-3 draws
  if (k >= 4) {
    for (int t1 = 0; t1 < N; t1++) {
      if (t1 == ti) continue;
      for (int t2 = t1+1; t2 < N; t2++) {
	if (t2 == ti) continue;
	for (int t3 = t2+1; t3 < N; t3++) {
	  if (t3 == ti) continue;
	  
	  int pos = ti - (t1 < ti) - (t2 < ti) - (t3 < ti);
	  if (pos+1 <= k-3) {
	    total += prob3[t1][t2][t3];
	  }
	}
      }
    }
  }

  return total;

}

int main()
{
  cin >> N;
  team.resize(N);
  for (int i = 0; i < N; i++) {
    cin >> team[i].balls >> team[i].name;
  }

  precompute();
  
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    string t;
    int k;
    cin >> t >> k;

    int ti = -1;
    for (int i = 0; i < N; i++) {
      if (team[i].name == t) {
	ti = i;
      }
    }

    assert(ti != -1);

    cout << fixed << setprecision(10) << answer(ti, k) << endl;
  }


  
  return 0;
}
