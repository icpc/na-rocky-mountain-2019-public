#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const ull B = 27;
const ull MOD = 2147483659ULL;

int N;
vector<string> v;
set<pair<int,ull>> hashes;

ull hashf(const string &s)
{
  ull ans = 0;
  for (auto c : s) {
    ans = (ans * B) % MOD;
    ans = (ans + (c - 'a' + 1)) % MOD;
  }
  return ans;
}

ull powmod(ull B, int e)
{
  if (e == 0) return 1;
  if (e % 2 == 1) {
    return (powmod(B, e-1) * B) % MOD;
  } else {
    ull t = powmod(B, e/2);
    return (t * t) % MOD;
  }
}

bool typo(const string &s)
{
  ull prefix = 0, suffix = 0;
  int n = s.length();
  suffix = hashf(s.substr(1));
  for (int i = 0; i < n; i++) {
    ull val = ((powmod(B, n-i-1) * prefix) % MOD + suffix) % MOD;
    if (hashes.count(make_pair(n-1, val))) {
      return true;
    }
    prefix = (prefix * B) % MOD;
    prefix = (prefix + (s[i] - 'a' + 1)) % MOD;
    if (i+1 <= n-1) {
      ull sub = ((s[i+1] - 'a' + 1) * powmod(B, (n-1-(i+1)))) % MOD;
      suffix = (suffix + (MOD - sub)) % MOD;
    }
  }
  return false;
}

int main()
{
  cin >> N;
  v.reserve(N);
  
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    v.push_back(s);
    hashes.insert(make_pair(s.length(), hashf(s)));
  }

  bool found = false;
  for (const auto &s : v) {
    if (typo(s)) {
      found = true;
      cout << s << endl;
    }
  }
  if (!found) {
    cout << "NO TYPOS" << endl;
  }
  return 0;
}
