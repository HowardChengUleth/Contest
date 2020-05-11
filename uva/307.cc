#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

int global_max;
int piece[10000][10000];

bool search(int sticks[51], int stick_num, int piece_num,
	    int max_len, int len, int total_len, bool check_lex = false,
	    int curr_len = 0)
{
  if (curr_len == len) {
    curr_len = 0;
    max_len = global_max;
    stick_num++;
    piece_num = 0;
    check_lex = true;
  }

  if (total_len + curr_len == len) {
    return true;
  }

  max_len = min(max_len, len-curr_len);
  while (max_len > 0 && sticks[max_len] == 0) {
    max_len--;
  }

  if (max_len == 0) {
    return false;
  }

  // the longest stick has to go somewhere, so let's use it if we are
  // starting a new stick
  if (piece_num == 0) {
    // there is no need to check lex because we are always taking the
    // longest remaining piece first
    sticks[max_len]--;
    piece[stick_num][piece_num] = max_len;
    if (search(sticks, stick_num, piece_num+1, max_len, len, 
	       total_len - max_len, check_lex && 
	       piece[stick_num][piece_num] == piece[stick_num-1][piece_num],
	       max_len)) {
	return true;
    }
    sticks[max_len]++;

    return false;
  }

  
  if (check_lex) {
    max_len = min(max_len, piece[stick_num-1][piece_num]);
    while (max_len > 0 && sticks[max_len] == 0) {
      max_len--;
    }
    if (max_len == 0) {
      return false;
    }
  }

  // try using it
  sticks[max_len]--;
  piece[stick_num][piece_num] = max_len;
  if (search(sticks, stick_num, piece_num+1, max_len, len,
	     total_len - max_len, check_lex && 
	     piece[stick_num][piece_num] == piece[stick_num-1][piece_num],
	     max_len + curr_len)) {
    return true;
  }
  sticks[max_len]++;

  // try not using it
  return search(sticks, stick_num, piece_num, max_len-1, len,
		total_len, check_lex, curr_len);
}

int solve(int sticks[51], int total)
{
  for (int len = global_max; len <= total/2; len++) {
    if (total % len != 0) continue;

    if (search(sticks, 0, 0, global_max, len, total))
      return len;
  }
  return total;
}

int main(void)
{
  int N;

  while (cin >> N && N > 0) {
    int sticks[51];
    fill(sticks, sticks+51, 0);
    
    int total = 0;
    global_max = 0;
    int len;
    for (int i = 0; i < N; i++) {
      cin >> len;
      sticks[len]++;
      total += len;
      global_max = max(global_max, len);
    }

    cout << solve(sticks, total) << endl;

  }

  return 0;
}
