class Node:
    def __init__(self, data: int):
        self.data = data
        self.next: Node | None = None


class HashSet:
    def __init__(self, initial_size: int, max_load_factor: float):
        if initial_size <= 0 or (initial_size & (initial_size - 1)) != 0:
            raise ValueError("initial size must be a power of 2")
        self.max_load_factor = max_load_factor
        self.num_elements = 0
        self.size = initial_size
        self.set = [None] * initial_size
    
    def __trailing_zeros(self, value: int):
        n = value
        num_zeros = 0
        while n > 1:
            n /= 2
            num_zeros+=1
        return num_zeros

    def __knuth_hash(self, value: int) -> int:
        return (value * 2654435761) & 0xFFFFFFFF

    def contains(self, value: int) -> bool:
        p = self.__trailing_zeros(self.size)
        index = self.__knuth_hash(value) >> (32-p)
        head = self.set[index]

        while head is not None:
            if head.data == value:
                return True
            head = head.next
        
        return False
    
    def remove(self, value: int) -> bool:
        p = self.__trailing_zeros(self.size)
        index = self.__knuth_hash(value) >> (32-p)
        head = self.set[index]
        next = None
        if head is None:
            return False
        next = head.next

        if head.data == value:
            self.set[index] = next
            self.num_elements-=1
            return True
        
        while next is not None:
            if next.data == value:
                head.next = next.next
                self.num_elements-=1
                return True
            next = next.next
        
        return False
    
    def __resize(self) -> None:
        new_size = 2 * self.size
        if self.__trailing_zeros(new_size) > 30:
            return None
        
        new_set = [None] * new_size
        head = None
        next = None
        new_head = None
        new_index = None
        p = self.__trailing_zeros(new_size)
        for i in range(0, self.size):
            head = self.set[i]
            while head is not None:
                next = head.next
                new_node = Node(head.data)
                new_index = self.__knuth_hash(head.data) >> (32-p)
                new_head = new_set[new_index]
                if new_head is None:
                    new_set[new_index] = new_node
                else:
                    while new_head.next is not None:
                        new_head = new_head.next
                    new_head.next = new_node
                head = next
        
        self.size = new_size
        self.set = new_set
        return None


    def add(self, value: int) -> bool:
        if self.contains(value):
            return False
        
        p = self.__trailing_zeros(self.size)
        index = self.__knuth_hash(value) >> (32-p)
        new_node = Node(value)
        current_node = self.set[index]
        if current_node is None:
            self.set[index] = new_node
            self.num_elements+=1
            if (self.num_elements / self.size) > 0.75:
                self.__resize()
            return True
        
        while current_node.next is not None:
            current_node = current_node.next
        
        current_node.next = new_node
        self.num_elements+=1
        if (self.num_elements / self.size) > 0.75:
            self.__resize()
        
        return True
    
    
    

