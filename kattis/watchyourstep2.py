xi, yi, xf, yf, x1, y1, x2, y2 = map(int, input().split())

ways = [[0 for _ in range(129)] for _ in range(129)]
ways[xi][yi] = 1

for x in range(xi, xf+1):
    for y in range(yi, yf+1):
        if x == xi and y == yi:
            continue
        
        ways[x][y] = 0
        if (x == x1 and y == y1) or (x == x2 and y == y2):
            continue

        if x > xi:
            ways[x][y] += ways[x-1][y]

        if y > yi:
            ways[x][y] += ways[x][y-1]
      
print(ways[xf][yf])

