#include <bits/stdc++.h>

using namespace std;

int N, K;
string s;

int memo[(1 << 20)+10];

int f(int used)
{
  if (used == 0) return 0;
  if (memo[used] >= 0) return memo[used];

  int chunks[26] = {0};
  char prev = -1;
  for (int i = 0; i < N; i++) {
    int c = s[i] - 'a';
    if (!((1 << c) & used)) continue;
    if (c != prev) {
      chunks[c]++;
    }
    prev = c;
  }

  memo[used] = N;
  for (int i = 0; i < 26; i++) {
    if (!chunks[i]) continue;
    int temp = chunks[i] + f(used ^ (1 << i));
    memo[used] = min(memo[used], temp);
  }
  return memo[used];
}

int main()
{
  int used = 0;
  cin >> N >> K;
  cin >> s;
  for (auto c : s) {
    used |= (1 << (c-'a'));
  }

  fill(memo, memo+(1<<20)+10, -1);
  cout << f(used) << endl;
  
  return 0;
}
