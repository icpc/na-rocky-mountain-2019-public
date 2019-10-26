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
  
  for (int i = 0; i < N; i++) {
    int count = 0;
    for (int j = 0; j < W; j++) {
      if (s[i+j] == 'Z') count++;
    }
    if (count < D) ans++;
  }
  cout << ans << endl;
}
