#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

int main()
{
  int N;
  ull A[200000], D;
  
  
  cin >> N >> D;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  ull ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      if (A[i]/D == A[j]/D) ans++;
    }
  }
  cout << ans << endl;
  return 0;
}
