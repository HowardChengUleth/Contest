#include <bits/stdc++.h>

using namespace std;

const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

typedef pair<int,int> pii;

bool inrange(pii p)
{
  return (0 <= p.first && p.first < 8 && 0 <= p.second && p.second < 8);
}

bool threaten_king(pii king1, pii king2)
{
  return max(abs(king1.first - king2.first), abs(king1.second - king2.second))
    <= 1;
}

bool check(pii myrook, pii myking, pii yourking)
{
  // has to be threatened first
  if (!((yourking.first == myrook.first || yourking.second == myrook.second)
	|| threaten_king(myking, yourking))) {
    return false;
  }

  // check if he can escape
  for (int i = 0; i < 8; i++) {
    pii king(yourking.first + dr[i], yourking.second + dc[i]);
    if (!inrange(king)) continue;
    if ((king.first == myrook.first || king.second == myrook.second) &&
	!(king == myrook)) {
      // threatened by rook, unless you capture the rook
      continue;
    }
    if (threaten_king(king, myking)) {
      // threatened by king
      continue;
    }

    // escape!
    return false;
  }

  return true;
}

int main()
{
  pii myking, yourking, myrook;
  
  char board[8][8];
  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 8; c++) {
      cin >> board[r][c];
      if (board[r][c] == 'K') {
	myking = pii(r,c);
      } else if (board[r][c] == 'k') {
	yourking = pii(r,c);
      } else if (board[r][c] == 'R') {
	myrook = pii(r,c);
      }
    }
  }

  pii rook, king;
  bool checkmate = false;
  for (int i = 0; i < 8; i++) {
    // move the rook up and down
    rook = myrook;
    rook.first = i;
    if (rook != myrook && rook != myking && rook != yourking) {
      checkmate |= check(rook, myking, yourking);
    }
    
    // move the rook left and right
    rook = myrook;
    rook.second = i;
    if (rook != myrook && rook != myking && rook != yourking) {
      checkmate |= check(rook, myking, yourking);
    }

    // move the king
    king.first = myking.first + dr[i];
    king.second = myking.second + dc[i];
    if (king != myrook && !threaten_king(king, yourking) &&
	king != yourking && inrange(king)) {
      checkmate |= check(myrook, king, yourking);
    }
  }

  cout << (checkmate ? "Yes" : "No") << endl;
  
  
  return 0;
}
