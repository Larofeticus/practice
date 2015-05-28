import random

p = [random.randint(1, 1000) for x in range(1,21)]

def minMax(A):
    if len(A) == 0:
        return ()
    mini = A[0]
    maxi = A[0]
    for x in range(1,len(A)-1, 2):
        i = A[x]
        j = A[x+1]
        if i > j:
            i,j = j,i
        if i < mini:
            mini = i
        if j > maxi:
            maxi = j
    if len(A) % 2 == 0:
        last = len(A)-1
        if A[last] < mini:
            mini = A[last]
        if A[last] > maxi:
            maxi = A[last]
    return (mini, maxi)

print(p)
print('(min, max): ',minMax(p))
