//
// This is dynamic programming.  First, we sort the students by usage time.
// At each time slot, the two benches can be in one of 25 configurations,
// and each of those configurations would have a minimum usage time to
// get to that configuration at that time slot.  So we just compute
// 20000 timeslots * 25 configurations = 500000 table entries.  Some work
// is required to remember the bench assignment for the optimal cost.
//

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;


const int MAX_SLOT = 20000;

struct User {
  int slot;        // time slot
  int inc;         // increment: 0 = 10 deg, 1 = 20, ..., 4 = 50 deg
  int orig_order;  // order in original input
  int bench_num;   // which bench user is assigned to

  // sorting by time slot
  bool operator<(const User &u) const
  {
    if (slot != u.slot) return slot < u.slot;
    return inc < u.inc;
  }
};

// sort back to the original order
bool orig_cmp(const User &u1, const User &u2)
{
  return u1.orig_order < u2.orig_order;
}

istream &operator>>(istream &is, User &u)
{
  is >> u.slot >> u.inc;
  u.inc = u.inc/10-1;
  return is;
}

User user[10000];

// [timeslot+1, bench1/10-1, bench2/10-1]
// best[i][j][k] = -1 if it is impossible to reach that configuration
//
// The cost stored includes only the cost for adjusting the benches
// (since the per user cost is fixed given the number of users).  Further,
// it is adjusted by a factor of 1/10.
int best[MAX_SLOT+3][5][5];

// pred1[i][j][k] is the inclination of bench 1 that is the predecessor
// used to compute best[i][j][k].
// pred2[i][j][k] is similar for bench 2
int pred1[MAX_SLOT+3][5][5];
int pred2[MAX_SLOT+3][5][5];

// copy data from given time slot to the next
void copy_data(int time_slot, int dest)
{
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      best[dest][i][j] = best[time_slot][i][j];
      pred1[dest][i][j] = pred1[time_slot][i][j];
      pred2[dest][i][j] = pred2[time_slot][i][j];
    }
  }
}

// extend the solution from [time_slot, inc1, inc2] to the next time
// slot with the given configuration
void extend(int time_slot, int inc1, int inc2, int new_inc1, int new_inc2)
{
  int temp = best[time_slot][inc1][inc2] + abs(new_inc1-inc1)
    + abs(new_inc2-inc2);
  if (best[time_slot+1][new_inc1][new_inc2] < 0 ||
      temp < best[time_slot+1][new_inc1][new_inc2]) {
    best[time_slot+1][new_inc1][new_inc2] = temp;
    pred1[time_slot+1][new_inc1][new_inc2] = inc1;
    pred2[time_slot+1][new_inc1][new_inc2] = inc2;
  }
}

// Assign the users to benches (backwards)
//
// inc1, inc2: the optimal configuration just after user[user_index] is served
void assign_benches(int inc1, int inc2, int user_index)
{
  if (user_index < 0) return;

  // trace back to the previous "active" time slot.
  int next1 = pred1[user[user_index].slot+1][inc1][inc2];
  int next2 = pred2[user[user_index].slot+1][inc1][inc2];
  
  if (user_index > 0 && user[user_index].slot == user[user_index-1].slot) {
    // if two users were served at the time slot
    
    // check the configuration vs. the user's inclinations
    if (inc1 == user[user_index].inc && inc2 == user[user_index-1].inc) {
      user[user_index].bench_num = 1;
      user[user_index-1].bench_num = 2;
    } else {
      assert(inc2 == user[user_index].inc && inc1 == user[user_index-1].inc);
      user[user_index].bench_num = 2;
      user[user_index-1].bench_num = 1;
    }
    assign_benches(next1, next2, user_index-2);
  } else {
      // only one user was served, match configuration with user inclination
    if (inc1 == user[user_index].inc) {
      user[user_index].bench_num = 1;
    } else {
      assert(inc2 == user[user_index].inc);
      user[user_index].bench_num = 2;
    }
    assign_benches(next1, next2, user_index-1);
  }
}

void do_case(void)
{
  int n;
  cin >> n;

  // read input and sort by time slot
  for (int i = 0; i < n; i++) {
    cin >> user[i];
    user[i].orig_order = i;
  }
  sort(user, user+n);

  // initially the only possible configuration is 10 degs on both benches
  for (int k = 0; k <= MAX_SLOT+2; k++) {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
	best[k][i][j] = -1;
      }
    }
  }
  best[0][0][0] = 0;

  // the following loop is a little tricky.  The best array is computed
  // for all time slots from 0 to 20000 (remember to add 1 for the real
  // index), but not the benches are not used at all of these times.
  // This makes things a bit complicated.  So we skip over the time slots 
  // that are not used.
  int user_index = 0;
  int time_slot = 0;
  for (time_slot = 0; user_index < n && time_slot <= MAX_SLOT; time_slot++) {
    // if the next user does not arrive in this time slot, just skip to
    // just before the next used time slot.
    if (time_slot < user[user_index].slot) {
      copy_data(time_slot, user[user_index].slot);
      time_slot = user[user_index].slot-1;  // -1 because it's incremented
                                            // at end of loop iteration
      continue;
    }
    
    // the next user needs to be served.
    int user_inc = -1;  // how many users are served at this time slot?

    // for each possible configuration from previous timeslot, try to
    // extend solution
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
	if (best[time_slot][i][j] < 0) continue;

	if (user_index+1 >= n || 
	    user[user_index+1].slot != user[user_index].slot) {
	  // this is the case when only one user is arriving at this
	  // time slot.

	  // try putting user on bench 1
	  int u1 = user[user_index].inc;
	  extend(time_slot, i, j, u1, j);

	  // try putting user on bench 2
	  extend(time_slot, i, j, i, u1);

	  user_inc = 1;
	} else {
	  // this is the case when two users are arriving at this time slot.

	  // try putting user 1 on bench 1, user 2 on bench 2
	  int u1 = user[user_index].inc;
	  int u2 = user[user_index+1].inc;
	  extend(time_slot, i, j, u1, u2);
	  
	  // try user 1 on bench 2, user 2 on bench 1
	  extend(time_slot, i, j, u2, u1);

	  user_inc = 2;
	}
      }
    }

    user_index += user_inc;
  }

  // if the last user is not at the last time slot, copy the result to
  // the end.
  copy_data(time_slot, MAX_SLOT+1);

  // now we have to move the benches back to 10 degrees at the end of the day,
  // so we account for that in one last step.
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (best[MAX_SLOT+1][i][j] < 0) continue;
      extend(MAX_SLOT+1, i, j, 0, 0);
    }
  }

  cout << best[MAX_SLOT+2][0][0]*10 + 15*n << endl;

  // now try to trace it back.  b1 and b2 are the configuration of the
  // two benches just before the end of the day adjustment leading
  // to the best cost.
  assign_benches(pred1[MAX_SLOT+2][0][0], pred2[MAX_SLOT+2][0][0], n-1);

  // now sort the users back to the original order and output bench
  // assignment.
  sort(user, user+n, orig_cmp);
  for (int i = 0; i < n; i++) {
    cout << user[i].bench_num << endl;
  }
}

int main(void)
{
  int C;
  cin >> C;
  while (C-- > 0) {
    do_case();
  }
  return 0;
}
