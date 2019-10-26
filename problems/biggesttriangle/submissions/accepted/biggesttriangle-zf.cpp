#include <iostream>
#include <algorithm>
#include <complex>
#include <vector>
#include <iomanip>

#define EPS 1e-8

using namespace std;

typedef double ld;

typedef complex<ld> point;

struct line {
  point p, q;
};

ld cross(point p, point q) {
  return imag(p*conj(q));
}

bool isect_iline(line l1, line l2, point& isect) {
  ld den = cross(l1.q-l1.p, l2.p-l2.q);

  if (fabs(den) < EPS) return false;

  ld num = cross(l2.p-l1.p, l2.p-l2.q);

  isect = l1.p + (l1.q-l1.p)*num/den;

  return true;
}

ld area(line l1, line l2, line l3) {
  point i1, i2, i3;

  if (!isect_iline(l1, l2, i1)) return 0;
  if (!isect_iline(l2, l3, i2)) return 0;
  if (!isect_iline(l3, l1, i3)) return 0;

  return abs(i1-i2) + abs(i2-i3) + abs(i3-i1);
}

int main() {
  int n;
  cin >> n;

  vector<line> lines(n);
  for (auto& l : lines) {
    ld x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    l.p = point(x1, y1);
    l.q = point(x2, y2);
  }

  ld best = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < i; ++j)
      for (int k = 0; k < j; ++k)
        best = max(best, area(lines[i], lines[j], lines[k]));

  cout.setf(ios::fixed);
  cout.precision(10);

  if (best < EPS) cout << "no triangle" << endl;
  else cout << best << endl;

  return 0;
}
