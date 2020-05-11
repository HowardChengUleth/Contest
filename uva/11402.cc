#define NDEBUG

#include <iostream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

struct Node
{
  int m_start, m_end;
  string m_s;            // meaningless if not a leaf, and we allow the
                         // possibility of |m_s| > m_end - m_start
  Node *m_left, *m_right;
  
  Node(int start = 0, int times = 0, const string &s = "")
    : m_start(start), m_s(s), m_left(0), m_right(0)
  {
    m_end = m_start + times * m_s.length();
  }

  Node(int start, int end, const string &s, int dummy)
    : m_start(start), m_end(end), m_s(s), m_left(0), m_right(0)
  {
  }

  Node(const vector<int> &T, const vector<string> &s, int M, int start,
       int index = 0)
  {
    if (M == 1) {
      m_start = start;
      m_s = s[index];
      m_end = start + T[index] * s[index].length();
      m_left = m_right = 0;
    } else {
      m_left = new Node(T, s, M/2, start, index);
      m_right = new Node(T, s, M - M/2, m_left->m_end, index + M/2);
      m_start = start;
      m_end = m_right->m_end;
    }
  }

  void print() const
  {
    if (m_left) {
      m_left->print();
      m_right->print();
      return;
    }

    int len = m_end - m_start;
    while (len > 0) {
      cout << m_s.substr(0, len);
      len -= m_s.length();
    }
  }

  ~Node()
  {
    delete m_left;
    delete m_right;
  }

  void adj_range(int &start, int &end)
  {
    start = max(m_start, start);
    end = min(m_end, end);
  }
  
  void fill(int start, int end, const char x[])
  {
    adj_range(start, end);
    if (start >= end) return;

    if (m_left) {
      // not leaf, just recurse
      assert(m_right);
      m_left->fill(start, end, x);
      m_right->fill(start, end, x);
      return;
    }

    // leaf node
    if (m_start == start && m_end == end) {
      // just replace string in node
      m_s = x;
      return;
    }
    
    Node *seg[3];
    int M = 0;

    // first part is [m_start, start)
    if (m_start < start) {
      seg[M++] = new Node(m_start, start, m_s, 999);
    }

    // second part is [start, end)
    seg[M++] = new Node(start, end, x, 999);

    // third part is [end, m_end)
    if (end < m_end) {
      int s_end = (end - m_start) % m_s.length();
      seg[M++] = new Node(end, m_end, m_s.substr(s_end) + m_s.substr(0, s_end),
			  999);
    } 

    if (M == 2) {
      m_left = seg[0];
      m_right = seg[1];
    } else {
      assert(M == 3);
      m_left = new Node(m_start, end, "", 999);
      m_left->m_left = seg[0];
      m_left->m_right = seg[1];
      m_right = seg[2];
    }
  }

  void flip(int start, int end)
  {
    adj_range(start, end);
    if (start >= end) return;

    if (m_left) {
      // not leaf, just recurse
      assert(m_right);
      m_left->flip(start, end);
      m_right->flip(start, end);
      return;
    }

    // leaf node
    if (m_start == start && m_end == end) {
      // just replace string in node
      for (unsigned int i = 0; i < m_s.length(); i++) {
	m_s[i] = (m_s[i] == '0') ? '1' : '0';
      }
      return;
    }

    Node *seg[3];
    int M = 0;
    
    // first part is [m_start, start)
    if (m_start < start) {
      seg[M++] = new Node(m_start, start, m_s, 999);
    }

    // second part is [start, end)
    int s_start = (start - m_start) % m_s.length();
    string s = m_s.substr(s_start) + m_s.substr(0, s_start);
    for (unsigned int i = 0; i < s.length(); i++) {
      s[i] = (s[i] == '0') ? '1' : '0';
    }
    seg[M++] = new Node(start, end, s, 999);

    // third part is [end, m_end)
    if (end < m_end) {
      int s_end = (end - m_start) % m_s.length();
      seg[M++] = new Node(end, m_end, m_s.substr(s_end) + m_s.substr(0, s_end),
			  999);
    } 

    if (M == 2) {
      m_left = seg[0];
      m_right = seg[1];
    } else {
      assert(M == 3);
      m_left = new Node(m_start, end, "", 999);
      m_left->m_left = seg[0];
      m_left->m_right = seg[1];
      m_right = seg[2];
    }
  }

  int count1(int start, int end)
  {
    // adjust the range
    adj_range(start, end);
    if (start >= end) return 0;
    
    if (m_left) {
      // not leaf, just recurse
      assert(m_right);
      return m_left->count1(start, end) + m_right->count1(start, end);
    }

    // leaf node
    unsigned int len = m_s.length();

    // figure out offset into the string at start and end
    int s_start = (start - m_start) % len;
    int s_end = (end - m_start) % len;
    int seg_start = (start - m_start) / len;
    int seg_end = (end - m_start) / len;

    // the number of segments covered by start to end, including
    // partial segments
    int ones[51] = {0};

    ones[0] = 0;
    for (unsigned int i = 1; i <= len; i++) {
      ones[i] = ones[i-1] + (m_s[i-1] == '1');
    }

    return ones[len] * (seg_end - seg_start + 1) -
      ones[s_start] - (ones[len] - ones[s_end]);
  }
};

void do_case()
{
  int M;
  cin >> M;

  vector<int> T(M);
  vector<string> s(M);

  for (int i = 0; i < M; i++) {
    cin >> T[i] >> s[i];
  }
  
  Node *root = new Node(T, s, M, 0);
  
  int Q, query_num = 1;
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    char cmd;
    int a, b;
    cin >> cmd >> a >> b;
    b++;                  // change to [a, b)
    switch (cmd) {
    case 'F':
      root->fill(a, b, "1");
      break;
    case 'E':
      root->fill(a, b, "0");
      break;
    case 'I':
      root->flip(a, b);
      break;
    case 'S':
      cout << "Q" << query_num++ << ": " << root->count1(a, b) << endl;
      break;
    }

//     cout << "map = ";
//     root->print();
//     cout << endl;
    
  }

  delete root;
}

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ":" << endl;
    do_case();
  }
  return 0;
}
