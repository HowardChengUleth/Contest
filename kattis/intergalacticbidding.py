#! /usr/bin/python3

n, s = input().split()
n = int(n)
s = int(s)

namelist = []
bidlist = []
usedlist = []
for i in range(n):
    name, bid = input().split()
    namelist.append(name)
    bidlist.append(int(bid))
    usedlist.append(False)

anslist = []
done = False
while not done:
    done = True
    best = -1
    besti = -1
    bestname = ""
    for i in range(len(namelist)):
        if bidlist[i] <= s and bidlist[i] > best and not usedlist[i]:
            best = bidlist[i]
            besti = i
            bestname = namelist[i]
            done = False
    if not done:
        anslist.append(bestname)
        usedlist[besti] = True
        s -= best

if s != 0:
   print(0)
else:
   print(len(anslist))
   for x in anslist:
       print(x)
  
