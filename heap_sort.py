import random

p = [random.randint(1, 1000) for x in range(1,20)]

print(p)

def left(i):
    return i<<1
def right(i):
    return i<<1 | 1
def parent(i):
    return i>>1

def heapify(A, i):
    l = left(i)
    r = right(i)
    largest = -1
    if l < len(A) and A[l] < A[i]:
        largest = l
    else:
        largest = i
    if r < len(A) and A[r] < A[largest]:
        largest = r
    if largest != i:
        A[i], A[largest] = A[largest], A[i]
        heapify(A, largest)

def buildHeap(A):
    for i in range (len(A)>>1, -1, -1):
        heapify(A, i)

def heapSort(A):
    if len(A) == 0:
        return A
    buildHeap(A)
    out = []
    while(len(A) > 1):
        out.append(A[0])
        A[0] = A.pop()
        heapify(A, 0)
    out.append(A[0])
    return out

def heapMin(A):
    if len(A) > 0:
        return A[0]
    return []

def heapMinExtract(A):
    if len(A) == 0:
        return []
    out = A[0]
    A[0] = A.pop()
    heapify(A, 0)
    return out

def heapDecreaseKey(A, i, key):
    if key > A[i]:
        return
    A[i] = key
    while (i > 1) and A[parent(i)] > A[i]:
        A[i], A[parent(i)] = A[parent(i)], A[i]
        i = parent(i)

def heapInsert(A, key):
    A.append(key)
    i = len(A)-1
    while (i > 1) and A[parent(i)] > A[i]:
        A[i], A[parent(i)] = A[parent(i)], A[i]
        i = parent(i)

hp = p[:]
buildHeap(hp)

print('heap: ',hp)

s = heapSort(p[:])

print('sorted: ', s)

print('min from heap: ', heapMin(hp), heapMinExtract(hp))
print('heap without min:       ', hp)

heapDecreaseKey(hp, 10, hp[10]>>1)
print('decrease a key by half: ', hp)

heapInsert(hp, 500)

print('insert 500: ', hp)
print('sorted after insert: ', heapSort(hp[:]))

