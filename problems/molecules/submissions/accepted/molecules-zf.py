#!/usr/bin/python3

EPS = 1e-8

def rref(a):
    n, m, r = len(a), len(a[0]), 0

    for c in range(m):
        piv = r
        while piv < n and abs(a[piv][c]) < EPS: piv += 1
        if piv == n: continue

        a[r], a[piv] = a[piv], a[r]

        for cc in range(m-1, c-1, -1): a[r][cc] /= a[r][c]

        for rr in range(n):
            if rr != r and abs(a[rr][c]) > EPS:
                for cc in range(m-1, c-1, -1):
                    a[rr][cc] -= a[r][cc]*a[rr][c]
        r += 1

n, m = map(int, input().split())

x, y = [], []
fixed = set()

for i in range(n):
    a, b = map(int, input().split())
    if (a, b) == (-1, -1):
        fixed.add(i)
    x.append(float(a))
    y.append(float(b))

g = {i:[] for i in range(n)}

for _ in range(m):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    g[u].append(v)
    g[v].append(u)

a = [[0.0]*(2*n+1) for _ in range(2*n)]

for i in range(n):
    a[2*i][2*i] = a[2*i+1][2*i+1] = 1.0
    if i in fixed:
        for j in g[i]:
            a[2*i][2*j] = a[2*i+1][2*j+1] = -1.0/len(g[i])
    else:
        a[2*i][2*n] = x[i]
        a[2*i+1][2*n] = y[i]

rref(a)
sol = [0.0]*(2*n)

for i in range(2*n):
    for j in range(2*n):
        if a[i][j] > 0.5:
            sol[j] = a[i][2*n]
            break

for i in range(n):
    print("{0:.10f} {1:.10f}".format(sol[2*i], sol[2*i+1]))
