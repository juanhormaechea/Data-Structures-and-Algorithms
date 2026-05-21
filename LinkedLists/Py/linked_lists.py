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
    
    def remove_node(self, index: int) -> int | None:
        if index < 0 or index > self._size-1:
            raise ValueError("index out of bounds")

        if index == 0:
            assert self.head is not None
            value = self.head.data
            self.head = self.head.next
            self._size-=1
            return value
        
        prev = self.head
        for i in range(1, index):
            assert prev is not None
            prev = prev.next
        
        assert prev is not None
        node_to_remove = prev.next
        assert node_to_remove is not None
        node_to_link = node_to_remove.next
        value = node_to_remove.data
        prev.next = node_to_link
        self._size-=1
        return value
    
    def search_node(self, node: int) -> int | None:
        head = self.head
        index = 0
        while head is not None:
            if head.data == node:
                return index
            head = head.next
            index+=1
        
        return None
    
    
    def __merge(self, list1: Node | None, list2: Node | None) -> Node | None:
        if list1 is None:
            return list2
        
        if list2 is None:
            return list1
        
        if list1.data <= list2.data:
            list1.next = self.__merge(list1.next, list2)
            return list1
        else:
            list2.next = self.__merge(list1, list2.next)
            return list2
    
    def sort_list(self, list=None, size=None) -> Node | None:
        if self._size == 0:
            return None
        
        if size is None:
            return self.sort_list(self.head, self._size)

        if size <= 1:
            return list

        mid = size//2
        prev = list
        for i in range(0, mid-1):
            prev = prev.next
        
        head_right = prev.next
        prev.next = None

        sorted_left = self.sort_list(list, mid)
        sorted_right = self.sort_list(head_right, size-mid)

        self.head = self.__merge(sorted_left, sorted_right)
        return self.head

            
     
    
    
      

    
