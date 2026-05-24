class Node:
    def __init__(self, data: int):
        self.data = data
        self.next: Node | None = None


class Queue:
    def __init__(self):
        self.front: Node | None = None
        self.back: Node | None = None
        self._size = 0
    

    def enqueue(self, element: int) -> None:
        new_node = Node(element)
        if self._size == 0:
            self.front = new_node
            self.back = new_node
            self._size+=1
            return
        assert self.back is not None
        self.back.next = new_node
        self.back = new_node
        self._size+=1
        return
    
    def dequeue(self) -> int | None:
        if self._size == 0:
            return None
        assert self.front is not None
        dequeued_value = self.front.data
        next = self.front.next
        self.front = next
        self._size-=1
        return dequeued_value
    
    def peek(self) -> int | None:
        if self._size == 0:
            return None
        assert self.front is not None
        return self.front.data
    
    def isEmpty(self) -> bool:
        return (self._size == 0)
    
    def queueSize(self) -> int:
        return self._size
    

