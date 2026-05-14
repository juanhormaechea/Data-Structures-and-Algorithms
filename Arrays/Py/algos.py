

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

# O(n+k) time complexity where k is the max value in array
def counting_sort(arr):
    if len(arr) <= 0:
        return arr
    
    sorted_arr = [0] * (max(arr) + 1)
    
    for i in range(len(arr)):
        sorted_arr[arr[i]] += 1

    index = 0
    for i in range(max(arr) + 1):
        while (sorted_arr[i] > 0):
            arr[index] = i
            index += 1
            sorted_arr[i] -= 1
    
    return arr


def merge(left, right):
    if len(left) == 0:
        return right
    
    if len(right) == 0:
        return left
    
    result = []
    i = 0
    j = 0

    while (i < len(left) and j < len(right)):
        if left[i] <= right[j]:
            result.append(left[i])
            i+=1
        else:
            result.append(right[j])
            j+=1
    
    result.extend(left[i:])
    result.extend(right[j:])

    return result

# time complexity of O(n·log_2(n))
def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    
    mid = len(arr) // 2
    sorted_left = merge_sort(arr[:mid])
    sorted_right = merge_sort(arr[mid:])

    arr = merge(sorted_left, sorted_right)
    return arr



def linear_search(arr, target):
    for i in range(len(arr)):
        if arr[i] == target:
            return i
        
    return -1


def binary_search(arr, target):
    left = 0
    right = len(arr) - 1

    while (left <= right):
        mid = (left + right) // 2
        if (arr[mid] == target):
            return mid

        if (arr[mid] < target):
            left = mid + 1
        else:
            right = mid - 1
    
    return -1