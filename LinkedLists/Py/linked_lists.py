class Node:
    def __init__(self, data):
        self.data = data
        self.next = None


class LinkedList:
    def __init__(self):
        self.head = None
        self._size = 0
    
    def get_size(self):
        return self._size
    
    def append(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
            self._size+=1
            return
        
        head = self.head
        for i in range(1, self._size):
            head = head.next
        head.next = new_node
        self._size+=1
        return
    
    def pop(self):
        value = None
        if self._size == 0:
            return value
        
        if self._size == 1:
            value = self.head.data
            self.head = None
            self._size-=1
            return value
        
        head = self.head
        for i in range(1, self._size-1):
            head = head.next

        value = head.next.data
        head.next = None
        self._size-=1
        return value
     
    
    
      

    
