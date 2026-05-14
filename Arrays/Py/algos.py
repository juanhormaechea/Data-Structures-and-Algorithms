

# worst case time complexity of O(n^2)
def bubble_sort(arr):
    swap = False
    for i in range(len(arr)):
        swap = False
        for j in range(len(arr)-i-1):
            if arr[j] > arr[j+1]:
                swap_num = arr[j+1]
                arr[j+1] = arr[j]
                arr[j] = swap_num
                swap = True
        if not swap:
           break
    
    return arr

# time complexity of O(n^2)
def selection_sort(arr):
    for i in range(len(arr)):
        min = arr[i]
        index = i
        for j in range(i, len(arr)):
            if arr[j] < min:
                min = arr[j]
                index = j
        swap_num = arr[index]
        arr[index] = arr[i]
        arr[i] = swap_num
    
    return arr


# time complexity of O(n^2)
def insertion_sort(arr):
    for i in range(len(arr)-1):
        index = i+1
        for j in range(i+1):
            if arr[i+1] > arr[i]:
                break
            if arr[j] > arr[i+1]:
                index = j
                break
        
        if index != i+1:
            swap_num = arr[i+1]
            for a in range(i, index-1, -1):
                arr[a+1] = arr[a]
            arr[index] = swap_num
    
    return arr


# lomuto partitioning algorithm for quicksort
def partition(arr, lower, upper):
    if len(arr) <= 1:
        return lower
    i = lower
    pivot = arr[upper]
    for j in range(lower, upper):
        if arr[j] < pivot:
            swap = arr[j]
            arr[j] = arr[i]
            arr[i] = swap
            i+=1
    
    arr[upper] = arr[i]
    arr[i] = pivot
    if i == lower:
        return lower + 1
    
    return i

def quicksort(arr, lower=0, upper=None):
    if upper is None:
        upper = len(arr)-1
    if (upper - lower) > 0:
        pivot_index = partition(arr, lower, upper)
        quicksort(arr, lower, pivot_index-1)
        quicksort(arr, pivot_index, upper)
    
    return arr



