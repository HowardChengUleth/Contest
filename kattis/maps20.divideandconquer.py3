def expmod(b, n, m):
    if n == 0:
        return 1
    elif n % 2 == 0:
        return expmod((b*b)%m, n//2, m)
    else:
        return (expmod(b, n-1, m) * b) % m
        

b, d = map(int, input().split())

if d == 2:
    if b % 2 == 0:
        print("no")
    else:
        print("yes")
    exit()

e = d-1
while e % 2 == 0:
    e //= 2
    r = expmod(b, e, d)
    if r == d-1:
        print("yes")
        exit()

print("no")
    
