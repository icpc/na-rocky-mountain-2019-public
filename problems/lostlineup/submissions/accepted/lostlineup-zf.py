#!/usr/bin/python3

n = int(input())

vals = list(map(int, input().split()))

ord = [(-1, 1)] + [(vals[i], i+2) for i in range(n-1)]

print(*(y for x,y in sorted(ord)))
