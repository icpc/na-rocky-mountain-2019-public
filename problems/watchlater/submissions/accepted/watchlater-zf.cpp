#include <iostream>
#include <cstring>
#include <set>

using namespace std;

char watch[401];
int dp[1<<20], toint[256];
bool seen[26];
int n, k;

int solve(int rem) {
  if (!rem) return 0;

  if (dp[rem] == -1) {
    int clicks[20] = {0};
    int prev = -1;

    for (int i = 0; watch[i]; ++i) {
      int c = toint[watch[i]];
      if (rem&(1<<c)) {
        if (prev != c) ++clicks[c];
        prev = c;
      }
    }

    dp[rem] = 1000;
    for (int i = 0; i < k; ++i)
      if (rem&(1<<i))
        dp[rem] = min(dp[rem], clicks[i] + solve(rem^(1<<i)));
  }
  return dp[rem];
}

int main() {
  cin >> n >> k >> watch;

  memset(dp, -1, sizeof(dp));
  memset(toint, -1, sizeof(toint));

  int x = 0;
  for (int i = 0; watch[i]; ++i)
    if (toint[watch[i]] == -1)
      toint[watch[i]] = x++;

  cout << solve((1<<k)-1) << endl;
  return 0;
}
