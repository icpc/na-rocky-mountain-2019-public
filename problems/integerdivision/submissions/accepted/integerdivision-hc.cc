#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

int main()
{
  int N;
  ull A, D;
  map<ull, ull> freq;
  
  cin >> N >> D;
  while (N--) {
    cin >> A;
    freq[A/D]++;
  }

  ull ans = 0;
  for (auto p : freq) {
    ans += p.second * (p.second-1)/2;
  }
  cout << ans << endl;
  return 0;
}
