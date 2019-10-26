#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

using namespace std;

typedef long long ll;

const ll MOD = 0x7fffffff; // a prime
const ll X = 123456;       // nothing special
const ll XINV = 1473977140;

// hash by viewing s as a polynomial
// (s[0] being the highest-order coefficient)
ll fullhash(const string& s) {
  ll h = 0;
  for (char c : s) h = (h*X+c)%MOD;
  return h;
}

vector<string> dict;
unordered_map<ll, vector<ll>> hashes;

bool positive_hit(ll th, const string& s, int i) {
  if (hashes.find(th) == hashes.end()) return false;

  // Heuristic Idea: If we get here there it is "extremely unlikely" that it
  // will be a positive hit. If this is always true when we get here, the
  // total work done over all iterations will be linear in the size of the input.

  // Can prove that with a random X, the expected running time will be linear
  // even if we have the occasional "false positive" that led us here.

  // Double-check before printing s to rule out false positives.
  for (int j : hashes[th])
    if (s.substr(0, i) + s.substr(i+1, s.length()) == dict[j])
      return true;

  return false;
}

int main() {
  assert((X*XINV)%MOD == 1);

  int n;
  cin >> n;

  dict.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> dict[i];

    // probably no collisions (i.e. likely that all vectors in the map have size 1)
    hashes[fullhash(dict[i])].push_back(i);
  }

  bool typo = false;
  for (const string& s : dict) {
    bool thistypo = false;
    ll h = fullhash(s), partial = 0, XP = 1;

    // go through all hashes of all substrings that can be obtained
    // by deleting a single character
    for (int i = s.length()-1; i >= 0; --i) {
      ll nextpartial = (partial+s[i]*XP)%MOD;

      // compute the hash "th" obtained by deleting s[i] from s
      ll th = (h-nextpartial+MOD)%MOD;
      th = (th*XINV + partial)%MOD;

      if (positive_hit(th, s, i)) {
        cout << s << endl;
        typo = true;
        break;
      }

      partial = nextpartial;
      XP = (XP*X)%MOD;
    }
  }

  if (!typo) cout << "NO TYPOS" << endl;

  return 0;
}
