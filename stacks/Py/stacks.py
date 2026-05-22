class Node:
    def __init__(self, data: int):
        self.data = data
        self.next: Node | None = None

class Stack:
    
    def __init__(self):
        self.head: Node | None = None
        self._size = 0
    
    def push(self, data: int) -> None:
        new_node: Node = Node(data)
        new_node.next = self.head
        self.head = new_node
        self._size+=1
        return
    
    def pop(self) -> int | None:
        if self.head is None:
            return None

        value = self.head.data
        new_head = self.head.next
        self.head = new_head
        self._size-=1
        return value

    def peek(self) -> int | None:
        if self.head is None:
            return None
        
        return self.head.data
    
    def isEmpty(self) -> bool:
        return self._size == 0
    
    def stackSize(self) -> int:
        return self._size
    

