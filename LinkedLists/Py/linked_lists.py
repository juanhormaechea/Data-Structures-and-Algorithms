class Node:
    def __init__(self, data: int):
        self.data = data
        self.next: Node | None = None


class LinkedList:
    def __init__(self):
        self.head: Node | None = None
        self._size = 0
    
    def get_size(self) -> int:
        return self._size
    
    def append(self, data: int) -> None:
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
            self._size+=1
            return
        
        head = self.head
        assert head is not None
        for i in range(1, self._size):
            assert head.next is not None
            head = head.next
        head.next = new_node
        self._size+=1
        return
    
    def pop(self) -> int | None:
        value: int | None = None
        if self._size == 0:
            return value
        
        if self._size == 1:
            assert self.head is not None
            value = self.head.data
            self.head = None
            self._size-=1
            return value
        
        head = self.head
        assert head is not None
        for i in range(1, self._size-1):
            assert head.next is not None
            head = head.next

        assert head.next is not None
        value = head.next.data
        head.next = None
        self._size-=1
        return value
    
    def insert_node(self, data: int, index: int) -> None:
        if index < 0 or index > self._size:
            raise ValueError("index out of bounds")
        
        if index == 0:
            new_head = Node(data)
            new_head.next = self.head
            self.head = new_head
            self._size+=1
            return
        
        head = self.head
        assert head is not None
        for i in range(index - 1):
            assert head.next is not None
            head = head.next
        
        next_node = head.next
        new_node = Node(data)
        head.next = new_node
        new_node.next = next_node
        self._size+=1
        return
        

     
    
    
      

    
