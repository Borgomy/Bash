import random

def moreRandomAB(A,B):
    countDigits = int(input("Input count random numbers:"))
    arrRandomNumbers = []
    random.seed(version=2)
    for iteration in range(countDigits):
        arrRandomNumbers.append(random.randint(A,B))
    arrRandomNumbers = sortArr(arrRandomNumbers, countDigits)
    return arrRandomNumbers

def sortArr(arr, sizeArr)->list:
    checkEnd = False
    indexElm = 0
    checkP = False
    while not checkEnd:
        if arr[indexElm] > arr[indexElm+1]:
            buf = arr[indexElm]
            arr[indexElm] = arr[indexElm+1]
            arr[indexElm+1] = buf
            checkP = True
        indexElm += 1
        if indexElm == sizeArr-1:
            if checkP == True:
                indexElm = 0
                checkP = False
            else:
                checkEnd = True
    return arr


