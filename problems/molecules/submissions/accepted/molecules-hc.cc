#include <bits/stdc++.h>

using namespace std;

const int MAX_V = 100;  // TBD
const int MAX_N = 2*MAX_V;

// assume A is n x n
void row_reduce(double A[MAX_N][MAX_N], double b[MAX_N], int n,
		int lcrow[MAX_N])
{
  int rank = 0;
  for (int j = 0; j < n; j++) {
    int row = rank;
    for (int i = row+1; i < n; i++) {
      if (fabs(A[i][j]) > fabs(A[row][j])) {
	row = i;
      }
    }
    if (fabs(A[row][j]) < 1e-6) {
      lcrow[j] = -1;
      continue;
    }
    lcrow[j] = rank;
    
    for (int k = j; k < n; k++) {
      swap(A[rank][k], A[row][k]);
    }
    swap(b[rank], b[row]);

    for (int i = rank+1; i < n; i++) {
      double scale = A[i][j] / A[rank][j];
      for (int k = j; k < n; k++) {
	A[i][k] -= scale * A[rank][k];
      }
      b[i] -= scale * b[rank];
    }
    rank++;
  }
}

void backsolve(double A[MAX_N][MAX_N], double b[MAX_N], int n,
	       int lcrow[MAX_N], double x[MAX_N])
{
  for (int i = n-1; i >= 0; i--) {
    if (lcrow[i] < 0) {
      x[i] = rand() % 10 + 1;       // whatever
      continue;
    }
    int r = lcrow[i];
    x[i] = b[r];
    for (int j = i+1; j < n; j++) {
      x[i] -= A[r][j] * x[j];
    }
    x[i] /= A[r][i];
  }
}

int main()
{
  double A[MAX_N][MAX_N], x[MAX_N], b[MAX_N];
  int n, m;
  bool known[MAX_N] = {false};
  
  cin >> n >> m;

  for (int i = 0; i < 2*n; i++) {
    for (int j = 0; j < 2*n; j++) {
      A[i][j] = 0;
    }
    b[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    double x, y;
    cin >> x >> y;
    if (!(x == -1.0 && y == -1.0)) {
      A[2*i][2*i] = A[2*i+1][2*i+1] = 1;
      b[2*i] = x;
      b[2*i+1] = y;
      known[i] = true;
    }
  }
  
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;       // assume 1-based
    u--; v--;

    if (!known[u]) {
      A[2*u][2*u]++;
      A[2*u+1][2*u+1]++;
      A[2*u][2*v] = -1;
      A[2*u+1][2*v+1] = -1;
    }
    if (!known[v]) {
      A[2*v][2*v]++;
      A[2*v+1][2*v+1]++;
      A[2*v][2*u] = -1;
      A[2*v+1][2*u+1] = -1;
    }
  }

  int lcrow[MAX_N];
  row_reduce(A, b, 2*n, lcrow);
  backsolve(A, b, 2*n, lcrow, x);
  for (int i = 0; i < n; i++) {
    cout << fixed << setprecision(10) << x[2*i] << ' ' << x[2*i+1] << endl;
  }
  


  
  return 0;
}
