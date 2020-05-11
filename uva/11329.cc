//
// The idea is this:
//
// start with the initial configuration, and do a BFS until we find a
// configuration in which every side of the die has a flea.
//
// The trick is to figure out how to represent the configuration so that
// the same configuration is not visited twice.  I use an integer:
//
// bits  0- 3: col and row of the die position
// bits  4- 9: which sides of the die has a flea
// bits 10-25: which board positions has a flea
//
// There are not that many different states, so this should be okay.
// The tricky part is to deal with the representation with bit operations.
//

#include <iostream>
#include <map>
#include <queue>
#include <utility>

using namespace std;

// a die is represented as 6-bit number: 0 means no flea, 1 means flea
// the faces are labeled as follows:
//
// 
//      4      
//      0 1 2 3
//      5      
//
// where face 0 is on top, 4 is north

// how to turn the die
int die_W(int x)
{
  return (x & 0x30) | ((x & 1) << 3) | ((x & 0xE) >> 1);
}

int die_E(int x)
{
  return (x & 0x30) | ((x & 7) << 1) | ((x & 8) != 0);
}

int die_N(int x)
{
  int b0 = (x & 1) != 0, b1 = (x & 2) != 0, b2 = (x & 4) != 0, 
    b3 = (x & 8) != 0, b4 = (x & 16) != 0, b5 = (x & 32) != 0;

  return b5 | (b1 << 1) | (b4 << 2) | (b3 << 3) | (b0 << 4) | (b2 << 5);
}

int die_S(int x)
{
  int b0 = (x & 1) != 0, b1 = (x & 2) != 0, b2 = (x & 4) != 0, 
    b3 = (x & 8) != 0, b4 = (x & 16) != 0, b5 = (x & 32) != 0;

  return b4 | (b1 << 1) | (b5 << 2) | (b3 << 3) | (b2 << 4) | (b0 << 5);
}


// given the new location, new die configuration, and current board 
// configuration, produce a new configuration
int move(int board, int nr, int nc, int die_config)
{
  int k = (nr << 2) | nc;
  
  if (board & (1 << k)) {
    if (!(die_config & 4)) {
      die_config |= 4;
      board &= ~(1 << k);
    } else {
      // do nothing if both the die and the board has a flea
    }
  } else if (die_config & 4) {
    board |= (1 << k);
    die_config &= ~4;
  }
  return (board << 10) | (die_config << 4) | k;
}

int main(void)
{
  int cases;

  cin >> cases;

  while (cases-- > 0) {
    int die_pos;
    int k = 0;
    int board = 0;
    int die_config;   /* least 4 bits is the position, bits 4-9 gives the
                         sides which have fleas */
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++, k++) {
	char c;
	cin >> c;
	if (c == 'X') {
	  board |= (1 << k);
	} else if (c == 'D') {
	  die_pos = k;
	}
      }
    }

    // form the initial configuration
    int v = (board << 10) | die_pos;


    // do the BFS
    bool found = false;
    map<int, int> dist;
    queue<int> q;

    dist[v] = 0;
    q.push(v);
    while (!q.empty()) {
      v = q.front();
      q.pop();
      die_config = (v & 0x3FF) >> 4;
      int d = dist[v];
      if (die_config == 0x3F) {
	cout << d << endl;
	found = true;
	break;
      }
      
      int row = (v & 0xF) >> 2;
      int col = (v & 0x3);
      int board = v >> 10;
      if (row > 0) {
	int w = move(board, row-1, col, die_N(die_config));
	if (dist.insert(pair<int,int>(w,d+1)).second) {
	  q.push(w);
	}
      }
      if (row < 3) {
	int w = move(board, row+1, col, die_S(die_config));
	if (dist.insert(pair<int,int>(w,d+1)).second) {
	  q.push(w);
	}
      }
      if (col > 0) {
	int w = move(board, row, col-1, die_W(die_config));
	if (dist.insert(pair<int,int>(w,d+1)).second) {
	  q.push(w);
	}
      }
      if (col < 3) {
	int w = move(board, row, col+1, die_E(die_config));
	if (dist.insert(pair<int,int>(w,d+1)).second) {
	  q.push(w);
	}
      }
    }
    if (!found) {
      cout << "impossible" << endl;
    }
  }
  return 0;
}
