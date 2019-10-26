#!/usr/bin/python3
EPS = 1e-8

def cross(p, q):
    return (p*q.conjugate()).imag

def isect(l1, l2):
    den = cross(l1[1]-l1[0], l2[0]-l2[1])
    if abs(den) < EPS: return None

    num = cross(l2[0]-l1[0], l2[0]-l2[1])

    return l1[0]+(l1[1]-l1[0])*num/den

def area(l1, l2, l3):
    i1 = isect(l1, l2)
    i2 = isect(l2, l3)
    i3 = isect(l3, l1)

    if None in [i1, i2, i3]: return 0.0

    return abs(i1-i2) + abs(i2-i3) + abs(i3-i1)

n = int(input())
lines = []

for _ in range(n):
    x1, y1, x2, y2 = map(float, input().split())
    lines.append([complex(x1, y1), complex(x2, y2)])

best = 0.0
for i in range(n):
    for j in range(i):
        for k in range(j):
            best = max(best, area(lines[i], lines[j], lines[k]))

if abs(best) < EPS:
    print("no triangle")
else:
    print("{0:.10f}".format(best))
