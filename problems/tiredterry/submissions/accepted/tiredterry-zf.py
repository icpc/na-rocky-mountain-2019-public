#!/usr/bin/python3

n, w, d = map(int, input().split())

sleep, num = 0, 0

zzz = input()*3

for i in range(2*n):
    if zzz[i] == "Z": sleep += 1
    if i-w >= 0 and zzz[i-w] == "Z": sleep -= 1

    if i >= n and sleep < d: num += 1

print(num)
