#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, W, D;
  cin >> N >> W >> D;

  string s;
  cin >> s;
  s += s;

  int ans = 0;
  
  int count = 0;
  for (int i = 0; i < W; i++) {
    count += (s[i] == 'Z');
  }

  for (int i = 0; i < N; i++) {
    if (count < D) ans++;
    count += (s[i+W] == 'Z');
    count -= (s[i] == 'Z');
  }
  cout << ans << endl;
}
