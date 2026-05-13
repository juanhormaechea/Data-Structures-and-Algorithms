

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

