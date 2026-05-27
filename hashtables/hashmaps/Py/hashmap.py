class Node:
    def __init__(self, key: int, value: int):
        self.key = key
        self.value = value
        self.next: Node | None = None

class HashMap:
    def __init__(self, size: int, max_load_factor: int):
        if size <= 0 or (size & (size - 1)) != 0:
            raise ValueError("size must be a power of 2")
        self.size = size
        self.max_load_factor = max_load_factor
        self.map = [None] * size
        self.num_elements = 0
    
    def __trailing_zeros(self, value: int) -> int:
        n = value
        num_zeros = 0
        while n > 1:
            n //= 2
            num_zeros += 1
        return num_zeros
    
    def __knuth_hash(self, value: int) -> int:
        return (value * 2654435761) & 0xFFFFFFFF
    
    def get(self, key: int) -> int | None:
        p = self.__trailing_zeros(self.size)
        index = self.__knuth_hash(key) >> (32 - p)
        node = self.map[index]
        if node is None:
            return None
        
        while node is not None:
            if node.key == key:
                return node.value
            node = node.next
        
        return None
    
    def __resize(self) -> None: 
        new_size = 2 * self.size
        p = self.__trailing_zeros(new_size)
        if p > 30:
            return None
    
        new_map = [None] * new_size
        head = None
        next = None
        new_head = None
        new_index = None
        for i in range(0, self.size):
            head = self.map[i]
            while head is not None:
                next = head.next
                new_node = Node(head.key, head.value)
                new_index = self.__knuth_hash(head.key) >> (32 - p)
                new_head = new_map[new_index]
                if new_head is None:
                    new_map[new_index] = new_node
                else:
                    while new_head.next is not None:
                        new_head = new_head.next
                    new_head.next = new_node
                head = next
        
        self.size = new_size
        self.map = new_map


    def add(self, key: int, value: int) -> None:

        p = self.__trailing_zeros(self.size)
        index = self.__knuth_hash(key) >> (32 - p)
        head = self.map[index]
        new_node = None
        if head is None:
            new_node = Node(key, value)
            self.map[index] = new_node
            self.num_elements+=1
            if (self.num_elements / self.size) > self.max_load_factor:
                self.__resize()
            return None
        
        while head.next is not None:
            if head.key == key:
                head.value = value
                return None
            head = head.next
        
        if head.key == key:
            head.value = value
        else:
            new_node = Node(key, value)
            head.next = new_node
            self.num_elements+=1
            if (self.num_elements / self.size) > self.max_load_factor:
                self.__resize()
        return None
    
    def remove(self, key: int) -> bool:
        p = self.__trailing_zeros(self.size)
        index = self.__knuth_hash(key) >> (32 - p)
        head = self.map[index]
        next = None
        if head is None:
            return False
        
        next = head.next

        if head.key == key:
            self.map[index] = next
            self.num_elements-=1
            return True
        
        while next is not None:
            if next.key == key:
                head.next = next.next
                self.num_elements-=1
                return True
            head = next
            next = next.next
        
        return False
    
    

            