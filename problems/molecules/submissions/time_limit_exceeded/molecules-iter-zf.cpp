#include <iostream>
#include <vector>
#include <complex>

#define MAXN 100
#define ITERATIONS 5000000

using namespace std;

typedef complex<double> point;

int main() {
  int n, m;
  vector<int> g[MAXN];
  point pts[MAXN], tmp[MAXN];
  bool anchored[MAXN];

  cin >> n >> m;

  for (int u = 0; u < n; ++u) {
    int x, y;
    cin >> x >> y;
    anchored[u] = (x != -1 || y != -1);
    pts[u] = point((double) x, (double) y);
  }

  while (m--) {
    int u, v;
    cin >> u >> v;
    g[--u].push_back(--v);
    g[v].push_back(u);
  }

  for (int iter = 0; iter < ITERATIONS; ++iter) {
    for (int u = 0; u < n; ++u) {
        if (anchored[u]) {
          tmp[u] = pts[u];
        }
        else {
          point delta(0.0, 0.0);
          for (int v : g[u]) delta += pts[v];
          tmp[u] = 0.5*pts[u] + 0.5*delta/double(g[u].size());
        }
    }
    for (int u = 0; u < n; ++u) pts[u] = tmp[u];
  }

  cout.setf(ios::fixed);
  cout.precision(10);

  for (int u = 0; u < n; ++u)
    cout << real(pts[u]) << ' ' << imag(pts[u]) << endl;

  return 0;
}
