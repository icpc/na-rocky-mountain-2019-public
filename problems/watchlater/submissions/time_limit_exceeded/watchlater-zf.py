#!/usr/bin/python3

def solve(rem):
    if rem == 0: return 0

    if rem not in memo:
        clicks = [0]*20
        prev = -1
        for c in watch:
            if rem&(1<<c) and prev != c:
                clicks[c] += 1
                prev = c
        memo[rem] = min(clicks[c] + solve(rem^(1<<c)) for c in range(k) if rem&(1<<c))

    return memo[rem]

n, k = map(int, input().split())
watch = input()

memo = {}
toint = {}

for c in watch:
    if c not in toint:
        toint[c] = len(toint)

watch = [toint[c] for c in watch]

print(solve((1<<k)-1))
