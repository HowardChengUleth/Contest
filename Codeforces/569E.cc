#include <bits/stdc++.h>

using namespace std;

// If we look at whether a position is a vowel or not, we can think of
// each position as a boolean variable that is either true (vowel) or
// false (consonant).
//
// Each rule they give is basically an implication between two variables.
// e.g. 1 C 2 V   translates to not(v1) -> v2
//
// Also, if we know any the letter to be used for any particular position,
// then we want to force that variable to be true if it's a vowel, or false otherwise.
// Notice that all such relationships can be specified by an OR of two (possibly
// negated) variables.
//
// So to check whether a particular string is in the dictionary, we just set up a 2-SAT
// problem and ask if there is a solution.  If the given string is in the dictionary
// then we found the answer.
//
// Otherwise, we try to see if it is possible to use the first k letters of the given
// string, increment the (k+1)st letter, and see if there is solution.  Doing this
// with decreasing k means that the first time a solution is found, we have
// determined the prefix of the answer.
//
// Then we work forward again to fill in the solution one character at a time.
//


// The following is the 2-SAT code in the NAIPC library, but I have changed the
// structure to pull out the graphs into global space so they are not reallocated
// for every call of 2-SAT.


vector<vector<int>> G, H;
vector<int> ord, comp;
vector<bool> V;

struct SCC {
  int n, c;
  SCC(int n) : n(n) {
    G.resize(n);
    H.resize(n);
    for (int i = 0; i < n; i++) {
      G[i].reserve(n);
      H[i].reserve(n);
      G[i].clear();
      H[i].clear();
    }
    ord.reserve(n);
    ord.clear();
  };
  void add_edge(int u, int v) {
    G[u].push_back(v);
    H[v].push_back(u);
  }
  void dfs1(int v) { 
    V[v] = true;
    for (auto& u : G[v])
      if (!V[u]) dfs1(u);
    ord.push_back(v);
  }
  void dfs2(int v) {
    comp[v] = c;
    for (auto& u : H[v])
      if (comp[u] == -1) dfs2(u);
  }
  vector<int> scc() {
    V.assign(n, 0);
    for (int i = 0; i < n; i++)
      if (!V[i]) dfs1(i);
    comp.assign(n, -1); c = 0;
    for (int i = 0; i < n; i++) {
      int v = ord[n-1-i];
      if (comp[v] == -1) dfs2(v), c++;
    }
    return comp;
  }
  vector<vector<int>> dag() {
    set<pair<int, int>> S;
    vector<vector<int>> dag(c);
    for (int a = 0; a < n; a++) {
      for (auto& b : G[a]) {
        if (comp[a] == comp[b]) continue;
        if (!S.count({comp[a], comp[b]})) {
          dag[comp[a]].push_back(comp[b]);
          S.insert({comp[a], comp[b]});
        }
      }
    }
    return dag;
  }
};


/*  Include SCC code
 *  O(n) solve 2SAT problem:
 *  solve().fst = T/F if there is a valid assignment
 *  solve().snd = vector<bool> containing the valid assignments.
 */
int VAR(int i) { return 2*i; }
int NOT(int i) { return i^1; }
struct SAT {
  int n; SCC scc;
  SAT(int n) : n(n), scc(2*n) {}
  void add_or(int a, int b) {
    if (a == NOT(b)) return;
    scc.add_edge(NOT(a), b);
    scc.add_edge(NOT(b), a);
  }
  void add_true(int a) { add_or(a, a); }
  void add_false(int a) { add_or(NOT(a), NOT(a)); }
  void add_xor(int a, int b) { add_or(a, b); add_or(NOT(a), NOT(b)); }
  void add_imply(int a, int b) { add_or(NOT(a), b); }
  
  bool solve() {
    auto comp = scc.scc();
    for (int i = 0; i < 2*n; i += 2) {
      if (comp[i] == comp[i+1]) return false;
    }
    return true;
  }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Problem-specific code
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// stores a rule.  pos1, pos2 are the variable indices to be used for the 2-SAT
// code
struct Rule
{
  int pos1, pos2;
  char t1, t2;
  void read()
  {
    cin >> pos1 >> t1 >> pos2 >> t2;
    pos1 = VAR(pos1-1);
    pos2 = VAR(pos2-1);
    if (t1 == 'C') pos1 = NOT(pos1);
    if (t2 == 'C') pos2 = NOT(pos2);
  }
};

string alpha, s;
int l, n, m;

// indexed by character, remembers whether a char is vowel or not
bool vowel[256];
Rule rule[4*200*199];

// indexed by character, remembers the next smallest vowel or consonant, or
// '\0' if there is none
char next_vowel[256], next_cons[256];

// remembers the smallest vowel or consonent, or '\0' if there is none.
char min_v, min_c;

// checks if the first pl characters of the string s (global) can be completed to
// a word in the dictionary.  next_greater means whether the (pl+1)st character
// is forced to be greater than what is in s
bool check_str(int pl, bool next_greater = true)
{
  SAT sat(2*n);

  // special cases
  if (!min_c) {
    // everything is a vowel
    for (int i = 0; i < n; i++) {
      sat.add_true(VAR(i));
    }
  } else if (!min_v) {
    // everything is a consonant
    for (int i = 0; i < n; i++) {
      sat.add_false(VAR(i));
    }
  }

  // add the given rules
  for (int i = 0; i < m; i++) {
    sat.add_imply(rule[i].pos1, rule[i].pos2);
  }

  // prefix has to be fixed by what is in s
  for (int i = 0; i < pl; i++) {
    if (vowel[s[i]]) {
      sat.add_true(VAR(i));
    } else {
      sat.add_false(VAR(i));
    }
  }

  // next letter has to be greater: do we have a vowel or consonant that is bigger?
  // If only one or the other, then there is more restriction on that position
  if (pl < n && next_greater) {
    char ch = s[pl];
    if (!next_vowel[ch] && !next_cons[ch]) {
      // no way to continue
      return false;
    }
    if (next_vowel[ch] && !next_cons[ch]) {
      // must be a vowel
      sat.add_true(VAR(pl));
    }
    if (!next_vowel[ch] && next_cons[ch]) {
      // must be a consonant
      sat.add_false(VAR(pl));
    }
  }
  
  return sat.solve();
}

// see if we can take the string s and:
//   - keep position 0..pos-1 the same
//   - change the pos into the given character
//   - pos+1..n-1 can be anything
bool try_ch(int pos, char ch)
{
  if (!ch) return false;
  
  char old = s[pos];
  s[pos] = ch;
  bool res = check_str(pos+1, false);
  s [pos]= old;
  return res;
}

string build_soln(int pl)
{
  if (pl >= n) return s;
  string ans = s;
   
  // deal with next letter: only need to check the next vowel and/or next consonant
  // and choose the smallest one that works.
  char ch = 127;
  if (try_ch(pl, next_vowel[s[pl]])) {
    ch = min(ch, next_vowel[s[pl]]);
  }
  if (try_ch(pl, next_cons[s[pl]])) {
    ch = min(ch, next_cons[s[pl]]);
  }
  ans[pl] = ch;

  // the rest of the characters are the smallest vowel or the smallest
  // consonant, whichever one works and is smallest.
  for (int i = pl+1; i < n; i++) {
    ch = 127;
    s = ans;
    if (try_ch(i, min_v)) {
      ch = min(ch, min_v);
    }
    if (try_ch(i, min_c)) {
      ch = min(ch, min_c);
    }
    ans[i] = ch;
  }
  
  return ans;
}

int main()
{
  cin >> alpha;
  l = alpha.length();
  for (int i = 0, j = 'a'; i < l; i++, j++) {
    vowel[j] = alpha[i] == 'V';
  }

  min_v = min_c = 0;
  for (int i = 'a'+l-1; i >= 'a'; i--) {
    next_vowel[i] = min_v;
    next_cons[i] = min_c;
    if (vowel[i]) {
      min_v = i;
    } else {
      min_c = i;
    }
  }
  
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    rule[i].read();
  }

  cin >> s;

  int prefix_len = n;
  while (prefix_len >= 0 && !check_str(prefix_len)) {
    prefix_len--;
  }

  if (prefix_len < 0) {
    cout << -1 << endl;
    return 0;
  }

  cout << build_soln(prefix_len) << endl;
  
  return 0;
}
