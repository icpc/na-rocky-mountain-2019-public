#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip>

#define EPS 1e-8

using namespace std;

void rref(vector<vector<double>>& a) {
    if (!a.size()) return; // empty matrix!

    int n = a.size(), m = a[0].size();

    for (int r = 0, c = 0; c < m; ++c) {
        int piv = r;
        while (piv < n && fabs(a[piv][c]) < EPS) ++piv;
        if (piv == n) continue;
        swap(a[r], a[piv]);

        for (int cc = m-1; cc >= c; --cc) a[r][cc] /= a[r][c];

        for (int rr = 0; rr < n; ++rr)
            if (rr != r && fabs(a[rr][c]) > EPS)
                for (int cc = m-1; cc >= c; --cc)
                    a[rr][cc] -= a[r][cc]*a[rr][c];
        ++r;
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> x(n), y(n);
    vector<vector<int>> g(n);
    vector<vector<double>> a(2*n, vector<double>(2*n+1, 0.0));

    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];

    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        g[--u].push_back(--v);
        g[v].push_back(u);
    }

    for (int i = 0; i < n; ++i) {
        a[2*i][2*i] = a[2*i+1][2*i+1] = 1.0;

        if (x[i] == -1 && y[i] == -1) {
            for (int k : g[i])
                a[2*i][2*k] = a[2*i+1][2*k+1] = -1.0/g[i].size();
        }
        else {
            a[2*i][2*n] = x[i];
            a[2*i+1][2*n] = y[i];
        }
    }

    rref(a);

    vector<double> sol(2*n, 0.0);

    // get a particular solution by using 0 for all free variables
    for (int i = 0; i < 2*n; ++i)
        for (int j = 0; j < 2*n; ++j)
            if (a[i][j] > 0.5) {
                sol[j] = a[i][2*n];
                break;
            }

    cout.setf(ios::fixed);
    cout.precision(10);

    for (int i = 0; i < n; ++i)
        cout << sol[2*i] << ' ' << sol[2*i+1] << endl;

    return 0;
}
