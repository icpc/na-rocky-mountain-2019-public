#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

int main()
{
  vector<pii> v;
  int N;
  cin >> N;

  v.emplace_back(-1, 1);
  for (int i = 0; i < N-1; i++) {
    int x;
    cin >> x; 
    v.emplace_back(x, i+2);
  }
  sort(begin(v), end(v));
  for (auto p : v) {
    cout << p.second << ' ';
  }
  cout << endl;
  return 0;
}
